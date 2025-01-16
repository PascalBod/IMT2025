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
    RTOS for ML presentation - solution to exercise 10.
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
#include <stdint.h>

#include "app_log.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "gpiointerrupt.h"
#include "sl_sleeptimer.h"

// Button 0.
#define BTN0_PORT gpioPortB
#define BTN0_PIN  2
#define BTN0_FILTER false

// External pin interrupt to be used. See section 24.3.10.1 of the Reference
// Manual for information about the interrupts which can be assigned to
// GPIO input pins.
#define EXT_PIN_INT 0

#define BUTTON_MIN_PERIOD_MS 300
#define BUTTON_MAX_PERIOD_MS 2000

#define WAIT_PERIOD_MS 5000

typedef enum {
  ST_WAIT_FIRST_PRESS,
  ST_WAIT_MIN_PERIOD,
  ST_WAIT_SECOND_PRESS,
  ST_WAIT_PERIOD,
  ST_ERROR,
} state_t;

static state_t current_state;

static sl_sleeptimer_timer_handle_t min_timer;
static sl_sleeptimer_timer_handle_t max_timer;

static volatile bool button_pressed_flag;
static volatile bool min_timeout_flag;
static volatile bool max_timeout_flag;

static void on_min_timeout(sl_sleeptimer_timer_handle_t *handle,
                           void *data) {

  (void)&handle;
  (void)&data;

  min_timeout_flag = true;

}

static void on_max_timeout(sl_sleeptimer_timer_handle_t *handle,
                           void *data) {

  (void)&handle;
  (void)&data;

  max_timeout_flag = true;

}

// Returns false in case of trouble.
static bool start_timer(sl_sleeptimer_timer_handle_t *handle,
                        uint32_t period_ms,
                        sl_sleeptimer_timer_callback_t callback) {

  sl_status_t rs = sl_sleeptimer_start_timer_ms(
      handle,
      period_ms,
      callback,
      NULL,     // No parameter for the callback function.
      0,        // Highest priority.
      0         // Flags
  );
  if (rs != SL_STATUS_OK) {
      app_log_error("Error from sl_sleeptimer_start_timer_ms: %lx\n", rs);
      return false;
  }
  return true;

}

// Returns false in case of trouble.
static bool stop_timer(sl_sleeptimer_timer_handle_t *handle) {

  sl_status_t rs = sl_sleeptimer_stop_timer(handle);
  if (rs != SL_STATUS_OK) {
      app_log_error("Error from sl_sleeptimer_stop_timer: %lx, reset\n",
                    rs);
      return false;
  }
  return true;

}

static void on_gpio_change(uint8_t intNo) {

  (void)intNo;
  button_pressed_flag = true;

}

static void init_gpio(void) {

  // Enable GPIO block clock.
  CMU_ClockEnable(cmuClock_GPIO, true);
  // Enable BTN0 GPIO pin.
  GPIO_PinModeSet(BTN0_PORT, BTN0_PIN, gpioModeInput, BTN0_FILTER);

  // Initialize the interrupt dispatcher component.
  GPIOINT_Init();
  // Assign the ISR to the interrupt that is used.
  GPIOINT_CallbackRegister(EXT_PIN_INT, on_gpio_change);
  // It is recommended to disable interrupts before configuring the GPIO pin
  // interrupt. See https://docs.silabs.com/gecko-platform/5.0.2/platform-emlib-efr32xg24/gpio#gpio-ext-int-config.
  GPIO_IntDisable(1 << EXT_PIN_INT);
  // Assign the interrupt to the GPIO pin.
  GPIO_ExtIntConfig(BTN0_PORT,
                    BTN0_PIN,
                    EXT_PIN_INT,
                    false,    // Rising edge.
                    true,     // Falling edge.
                    true      // Enable the interrupt.
                    );

}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{

  // To let us know which application we are running.
  app_log_info("10-Timer-application - v0.2.1\n");

  init_gpio();

  button_pressed_flag = false;
  min_timeout_flag = false;
  max_timeout_flag = false;

  current_state = ST_WAIT_FIRST_PRESS;

}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{

  bool bool_rs;

  switch (current_state) {
    case ST_WAIT_FIRST_PRESS:
      if (button_pressed_flag) {
          button_pressed_flag = false;
          app_log_info("Button pressed once\n");
          // Start button timer for minimal period.
          bool_rs = start_timer(&min_timer, BUTTON_MIN_PERIOD_MS,
                                on_min_timeout);
          if (!bool_rs) {
              current_state = ST_ERROR;
              break;
          }
          // Start button timer for maximal period.
          bool_rs = start_timer(&max_timer, BUTTON_MAX_PERIOD_MS,
                                on_max_timeout);
          if (!bool_rs) {
              current_state = ST_ERROR;
              break;
          }
          //
          current_state = ST_WAIT_MIN_PERIOD;
          break;
      }
      break;
    case ST_WAIT_MIN_PERIOD:
      if (min_timeout_flag) {
          min_timeout_flag = false;
          app_log_info("Min timeout\n");
          //
          current_state = ST_WAIT_SECOND_PRESS;
          break;
      }
      if (button_pressed_flag) {
          button_pressed_flag = false;
          app_log_warning("Button pressed too early, reset\n");
          // Stop running timers.
          bool_rs = stop_timer(&min_timer);
          if (!bool_rs) {
              current_state = ST_ERROR;
              break;
          }
          bool_rs = stop_timer(&max_timer);
          if (!bool_rs) {
              current_state = ST_ERROR;
              break;
          }
          current_state = ST_WAIT_FIRST_PRESS;
          break;
      }
      break;
    case ST_WAIT_SECOND_PRESS:
      if (button_pressed_flag) {
          button_pressed_flag = false;
          app_log_info("Button pressed twice\n");
          // Stop max period timer.
          bool_rs = stop_timer(&max_timer);
          if (!bool_rs) {
              current_state = ST_ERROR;
              break;
          }
          // Start timer for the wait period.
          start_timer(&max_timer, WAIT_PERIOD_MS, on_max_timeout);
          //
          current_state = ST_WAIT_PERIOD;
          break;
      }
      if (max_timeout_flag) {
          max_timeout_flag = false;
          app_log_warning("Max time elapsed, reset\n");
          //
          current_state = ST_WAIT_FIRST_PRESS;
          break;
      }
      break;
    case ST_WAIT_PERIOD:
      if (max_timeout_flag) {
          max_timeout_flag = false;
          app_log_info("**** End of wait, reset\n");
          //
          current_state = ST_WAIT_FIRST_PRESS;
          break;
      }
      if (button_pressed_flag) {
          button_pressed_flag = false;
          app_log_warning("Unexpected button press, reset\n");
          // Stop running timer.
          bool_rs = stop_timer(&max_timer);
          if (!bool_rs) {
              current_state = ST_ERROR;
              break;
          }
          current_state = ST_WAIT_FIRST_PRESS;
          break;
      }
      break;
    case ST_ERROR:
      break;
    default:
      app_log_error("Unexpected state: %d\n", current_state);
  }

}
