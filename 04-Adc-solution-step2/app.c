/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/*
    RTOS for ML presentation - solution to exercise 04.
    Copyright (C) 2024  Pascal Bodin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdbool.h>

#include "app_log.h"
#include "em_cmu.h"
#include "em_iadc.h"
#include "sl_sleeptimer.h"

// The frequencies of the clocks we will use.
#define CLK_SRC_ADC_FREQ  20000000
#define CLK_ADC_FREQ      10000000

// Period between two conversion requests, in ms.
#define CONVERSION_PERIOD_MS  1000

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{

  // Initialization structures. Default values.
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;

  // Single channel input structure, used to define the origin of the signal
  // to be converted.
  IADC_SingleInput_t singleInput = IADC_SINGLEINPUT_DEFAULT;

  // To let us know which application we are running.
  app_log("04-ADC-step2 - v0.1.0\n");

  // Enable ADC-block clock.
  CMU_ClockEnable(cmuClock_IADC0, true);

  // Calculate the prescale value to set CLK_SRC_ADC to the value we want,
  // and set it.
  init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

  // Configuration 0 is used by the single channel mode by default.
  // We will use the internal 1.21 V reference voltage, 2x oversampling, and
  // an analog gain of 0.5. Resolution resulting from the sampling rate is
  // 12 bits.
  initAllConfigs.configs[0].reference = iadcCfgReferenceInt1V2;
  initAllConfigs.configs[0].vRef = 1210;
  initAllConfigs.configs[0].osrHighSpeed = iadcCfgOsrHighSpeed2x;
  initAllConfigs.configs[0].analogGain = iadcCfgAnalogGain0P5x;
  // 0.5 gain means that full scale reading is 2 x 1.21 = 2.42 V.

  // Calculate the prescale value to set CLK_ADC to the value we want. If the
  // value is too high, it will automatically be adjusted.
  initAllConfigs.configs[0].adcClkPrescale =
      IADC_calcAdcClkPrescale(IADC0,
                              CLK_ADC_FREQ,
                              0, // Use current setting of CMU clock.
                              iadcCfgModeNormal,
                              init.srcClkPrescale);

  // As we don't have an external signal, we convert Avdd (the voltage
  // provided to the analog blocks). Read value is Avdd / 4 (see page 761 of
  // the Reference Manual). According to the Dev Kit schematic, it's Vmcu,
  // provided either by the 3.3 V regulator or by the battery.
  singleInput.posInput   = iadcPosInputAvdd;
  singleInput.negInput   = iadcNegInputGnd;

  // Initialize IADC
  IADC_init(IADC0, &init, &initAllConfigs);

  // Initialize a single-channel conversion
  IADC_initSingle(IADC0, &initSingle, &singleInput);

  // Start conversion.
  IADC_command(IADC0, iadcCmdStartSingle);

}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/

typedef enum {
  ST_WAIT_BEFORE_CONVERTING,
  ST_WAIT_CONVERSION,
} state_t;

void app_process_action(void)
{

  // A conversation was started by app_init. Consequently, first state must be
  // ST_WAIT_CONVERSION (see below).
  static state_t current_state = ST_WAIT_CONVERSION;

  // Number of ms elapsed since startup, the previous time we checked.
  static uint64_t prev_ms;

  // We use a very simple finite state automaton.
  switch (current_state) {
    case ST_WAIT_CONVERSION:
      // Do we have the result of the conversion?
      uint8_t count = IADC_getSingleFifoCnt(IADC0);
      if (count != 0) {
          // Yes.
          IADC_Result_t result = IADC_pullSingleFifoResult(IADC0);
          app_log("Result: %lu\n", result.data);
          // Quantization uses 12 bits: 4096 corresponds to 2.42 V.
          // => voltage = 2.42 * (4 * result) / 4096.
          // If we use mV instead of V, we can calculate using integers only:
          // voltage = (2420 * (4 * result)) / 4096
          uint32_t v = (2420 * 4 * result.data) / 4096;
          app_log("Voltage: %lu\n", v);
          // Now, start waiting before next conversion request.
          // See solution to exercise 03 for time value wrapping.
          uint64_t ticks = sl_sleeptimer_get_tick_count64();
          sl_status_t rs = sl_sleeptimer_tick64_to_ms(ticks, &prev_ms);
          if (rs != SL_STATUS_OK) {
              app_log_error("Error from sl_sleeptimer_tick64_to_ms: %lu\n", rs);
              return;
          }
          current_state = ST_WAIT_BEFORE_CONVERTING;
          break;
      }
      // At this stage, no result yet.
      break;
    case ST_WAIT_BEFORE_CONVERTING:
      uint64_t ticks = sl_sleeptimer_get_tick_count64();
      uint64_t ms;
      sl_status_t rs = sl_sleeptimer_tick64_to_ms(ticks, &ms);
      if (rs != SL_STATUS_OK) {
          app_log_error("Error from sl_sleeptimer_tick64_to_ms: %lu\n", rs);
          return;
      }
      if (ms - prev_ms > CONVERSION_PERIOD_MS) {
          IADC_command(IADC0, iadcCmdStartSingle);
          prev_ms = ms;
          current_state = ST_WAIT_CONVERSION;
      }
      // At this stage, we still have to wait.
      break;
    default:
      app_log_error("Unexpected state: %d\n", current_state);
      return;
  }

}
