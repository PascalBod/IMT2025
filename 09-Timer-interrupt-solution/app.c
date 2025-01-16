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
    RTOS for ML presentation - solution to exercise 09.
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
#include "sl_sleeptimer.h"

#define WAIT_PERIOD_MS 1000

static volatile bool timeout_flag;

static sl_sleeptimer_timer_handle_t timer;

static void on_timeout(sl_sleeptimer_timer_handle_t *handle,
                       void *data) {

  (void)&handle;
  (void)&data;

  timeout_flag = true;

}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{

  uint32_t wait_period_ticks;

  // To let us know which application we are running.
  app_log_info("09-Timer-interrupt - v0.2.0\n");

  timeout_flag = false;

  wait_period_ticks = sl_sleeptimer_ms_to_tick(WAIT_PERIOD_MS);

  sl_status_t rs = sl_sleeptimer_start_timer(
      &timer,
      wait_period_ticks,
      on_timeout,
      NULL,     // No parameter for the callback function.
      0,        // Highest priority.
      0         // Flags
  );
  if (rs != SL_STATUS_OK) {
      app_log_error("Error from sl_sleeptimer_start_timer_ms: %lx\n", rs);
  }


}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{

  if (timeout_flag) {
      timeout_flag = false;
      app_log_info("Timeout\n");

      uint32_t wait_period_ticks;

      wait_period_ticks = sl_sleeptimer_ms_to_tick(WAIT_PERIOD_MS);

      sl_status_t rs = sl_sleeptimer_start_timer(
          &timer,
          wait_period_ticks,
          on_timeout,
          NULL,     // No parameter for the callback function.
          0,        // Highest priority.
          0         // Flags
      );
      if (rs != SL_STATUS_OK) {
          app_log_error("Error from sl_sleeptimer_start_timer_ms: %lx\n", rs);
      }
  }

}
