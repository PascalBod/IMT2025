/*
    RTOS for ML presentation - solution to exercise 16.
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

#include "app_log.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "FreeRTOS.h"
#include "gpiointerrupt.h"
#include "queue.h"
#include "sl_udelay.h"
#include "task.h"

// Button 0.
#define BTN0_PORT gpioPortB
#define BTN0_PIN  2
#define BTN0_FILTER false

// External pin interrupt to be used. See section 24.3.10.1 of the Reference
// Manual for information about the interrupts which can be assigned to
// GPIO input pins.
#define EXT_PIN_INT 0

// Maximum delay for sl_udelay_wait: 100000 µs.
#define RESET_DELAY_US  100000

#define QUEUE_LENGTH    5
#define QUEUE_ITEM_WAIT_PERIOD_MS   10000

#define SHORT_PERIOD_MS 800
#define LONG_PERIOD_MS  1100

#define PRODUCER_1_ID   1
#define PRODUCER_2_ID   2

#define TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define TASK_PRIORITY   10

static QueueHandle_t queue;

static StaticTask_t xTaskBuffer_1;

static StackType_t  xStack_1[TASK_STACK_SIZE];

static StaticQueue_t xQueue;
static uint8_t xQueueStorage[QUEUE_LENGTH * sizeof(TickType_t)];

static void reset_on_fatal_error(void) {

  app_log_error("About to reset\n");
  sl_udelay_wait(RESET_DELAY_US);
  NVIC_SystemReset();

}

// GPIOINT_IrqCallbackPtrExt_t.
static void on_gpio_change(uint8_t intNo) {

  (void)intNo;

  TickType_t ticks = xTaskGetTickCountFromISR();
  // Return status is not tested, as in case of error we won't try to display
  // an error message, because we are in an ISR.
  // A possible solution, to handle an error:
  // - Add a task, with a queue, waiting for error messages.
  // - Send it an error message, in case of error.
  xQueueSendToBackFromISR(queue, &ticks, NULL);

}

static void counter_code(void *pvParameters) {

  (void)&pvParameters;

  uint32_t counter = 0;
  BaseType_t os_rs;
  TickType_t time_stamp;

  while (true) {
      // We could use an infinite timeout, i.e. no timeout. But using a finite
      // value allows for liveliness checking when no message is received
      // for a long period.
      os_rs = xQueueReceive(queue, &time_stamp, QUEUE_ITEM_WAIT_PERIOD_MS);
      if (os_rs == pdFALSE) {
          app_log_info("Counter - Queue empty\n");
          continue;
      }
      counter++;
      app_log_info("Counter - New key press at %lu - total: %lu\n",
                   time_stamp, counter);
  }

}

void count_init(void)
{

  TaskHandle_t xHandle;

  app_log_info("Button presses - v0.1.0\n");

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
                    true,     // Rising edge.
                    false,    // Falling edge.
                    true      // Enable the interrupt.
                    );

  // Create the queue. Important: must be created before creating
  // the tasks.
  queue = xQueueCreateStatic(QUEUE_LENGTH, sizeof(TickType_t),
                             xQueueStorage, &xQueue);
  if (queue == NULL) {
      app_log_error("Error from xQueueCreate");
      reset_on_fatal_error();
  }

  xHandle = xTaskCreateStatic(counter_code,
                              "counter",
                              TASK_STACK_SIZE,
                              NULL,
                              TASK_PRIORITY,
                              xStack_1,
                              &xTaskBuffer_1);
  if (xHandle == NULL) {
      app_log_error("NULL returned by xTaskCreateStatic\n");
      reset_on_fatal_error();
  }

}
