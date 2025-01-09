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
    RTOS for ML presentation - solution to exercise 02.
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
#include "em_gpio.h"

#define BTN0_PORT gpioPortB
#define BTN0_PIN  2
#define BTN0_FILTER false

static unsigned int pin_value;

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{

  // To let us know which application we are running.
  app_log("02-GpioInput - v0.1.0\n");

  // Enable GPIO-block clock.
  CMU_ClockEnable(cmuClock_GPIO, true);
  // Enable BTN0 GPIO pin.
  GPIO_PinModeSet(BTN0_PORT, BTN0_PIN, gpioModeInput, BTN0_FILTER);
  // Initialize pin_value.
  pin_value = GPIO_PinInGet(BTN0_PORT, BTN0_PIN);
  app_log("BTN0 pin value: %u\n", pin_value);

}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{

  // Read pin value, and display a message if it changed.
  unsigned int pv = GPIO_PinInGet(BTN0_PORT, BTN0_PIN);
  if (pv != pin_value) {
      app_log("New BTN0 pin value: %u\n", pv);
      pin_value = pv;
  }

}
