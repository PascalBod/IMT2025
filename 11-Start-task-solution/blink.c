/***************************************************************************//**
 * @file
 * @brief Blink examples functions
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
    RTOS for ML presentation - solution to exercise 11.
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

#include <stdint.h>

#include "sl_simple_led.h"
#include "sl_simple_led_instances.h"
#include "FreeRTOS.h"
#include "task.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#ifndef LED_INSTANCE
#define LED_INSTANCE               sl_led_led0
#endif

#ifndef TOOGLE_DELAY_MS
#define TOOGLE_DELAY_MS            1000
#endif

#define TOGGLE_G_DELAY_MS          1100
#define TOGGLE_B_DELAY_MS          1200

#ifndef BLINK_TASK_STACK_SIZE
#define BLINK_TASK_STACK_SIZE      configMINIMAL_STACK_SIZE
#endif

#ifndef BLINK_TASK_PRIO
#define BLINK_TASK_PRIO            20
#endif

#ifndef EXAMPLE_USE_STATIC_ALLOCATION
#define EXAMPLE_USE_STATIC_ALLOCATION      1
#endif

typedef struct {
  sl_led_t led;
  uint32_t period_ms;
} task_args_t;

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// The structures below will be passed as task arguments. Consequently,
// they must be allocated in static storage, i.e. at the outer level (this is
// NOT related to the use of the static keyword here :-) ).
static task_args_t task_args_r;
static task_args_t task_args_g;
static task_args_t task_args_b;

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void blink_task(void *arg);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize blink example.
 ******************************************************************************/
void blink_init(void)
{
  TaskHandle_t xHandle = NULL;

  task_args_r.led = sl_led_led0;
  task_args_r.period_ms = TOOGLE_DELAY_MS;

  task_args_g.led = sl_led_led1;
  task_args_g.period_ms = TOGGLE_G_DELAY_MS;

  task_args_b.led = sl_led_led2;
  task_args_b.period_ms = TOGGLE_B_DELAY_MS;

#if (EXAMPLE_USE_STATIC_ALLOCATION == 1)

  static StaticTask_t xTaskBuffer_r;
  static StaticTask_t xTaskBuffer_g;
  static StaticTask_t xTaskBuffer_b;
  static StackType_t  xStack_r[BLINK_TASK_STACK_SIZE];
  static StackType_t  xStack_g[BLINK_TASK_STACK_SIZE];
  static StackType_t  xStack_b[BLINK_TASK_STACK_SIZE];

  // Create Blink Task without using any dynamic memory allocation
  xHandle = xTaskCreateStatic(blink_task,
                              "blink task",
                              BLINK_TASK_STACK_SIZE,
                              (void *)&task_args_r,
                              tskIDLE_PRIORITY + 1,
                              xStack_r,
                              &xTaskBuffer_r);

  // Since puxStackBuffer and pxTaskBuffer parameters are not NULL,
  // it is impossible for xHandle to be null. This check is for
  // rigorous example demonstration.
  EFM_ASSERT(xHandle != NULL);

  xHandle = xTaskCreateStatic(blink_task,
                              "blink task",
                              BLINK_TASK_STACK_SIZE,
                              (void *)&task_args_g,
                              tskIDLE_PRIORITY + 1,
                              xStack_g,
                              &xTaskBuffer_g);
  EFM_ASSERT(xHandle != NULL);

  xHandle = xTaskCreateStatic(blink_task,
                              "blink task",
                              BLINK_TASK_STACK_SIZE,
                              (void *)&task_args_b,
                              tskIDLE_PRIORITY + 1,
                              xStack_b,
                              &xTaskBuffer_b);
  EFM_ASSERT(xHandle != NULL);

#else

  BaseType_t xReturned = pdFAIL;

  // Create Blink Task using dynamic memory allocation
  xReturned = xTaskCreate(blink_task,
                          "blink task",
                          BLINK_TASK_STACK_SIZE,
                          ( void * ) NULL,
                          tskIDLE_PRIORITY + 1,
                          &xHandle);

  // Unlike task creation using static allocation, dynamic task creation can very likely
  // fail due to lack of memory. Checking the return value is relevant.
  EFM_ASSERT(xReturned == pdPASS);

#endif
}

/*******************************************************************************
 * Blink task.
 ******************************************************************************/
static void blink_task(void *arg)
{
  task_args_t *task_args = (task_args_t *)arg;

  //Use the provided calculation macro to convert milliseconds to OS ticks
  const TickType_t xDelay = pdMS_TO_TICKS(task_args->period_ms);

  while (1) {
    //Wait for specified delay
    vTaskDelay(xDelay);

    // Toggle led
    sl_led_toggle(&task_args->led);
  }
}
