/*
    RTOS for ML presentation - solution to exercise 17.
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
#include <stdio.h>
#include <string.h>

#include "app_log.h"
#include "FreeRTOS.h"
#include "task.h"

#include "logger.h"
#include "utils.h"

// Queue length must be large enough to let the queue accept all logger_log
// calls before the logger task starts.
#define QUEUE_LENGTH    8
#define QUEUE_ITEM_WAIT_PERIOD_MS   10000

#define TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define TASK_PRIORITY   10

#define TIME_STAMPED_LOG_MAX_LENGTH (LOG_MAX_LENGTH + 10)

QueueHandle_t logger_queue;

static StaticQueue_t xQueue;
static uint8_t xQueueStorage[QUEUE_LENGTH * sizeof(logger_message_t)];

static StaticTask_t xTaskBuffer;
static StackType_t  xStack[TASK_STACK_SIZE];

static void logger_code(void *pvParameters) {

  (void)&pvParameters;

  BaseType_t os_rs;
  logger_message_t message;

  while (true) {
      os_rs = xQueueReceive(logger_queue, &message, QUEUE_ITEM_WAIT_PERIOD_MS);
      if (os_rs == pdFALSE) {
          app_log_info("Logger - Queue empty\n");
          continue;
      }
      // At this stage, we have a log message to print.
      app_log_info("%ld - %s\n", message.time_stamp, message.log);
  }

}

void logger_init(void) {

  TaskHandle_t xHandle;

  logger_queue = xQueueCreateStatic(QUEUE_LENGTH, sizeof(logger_message_t),
                                    xQueueStorage, &xQueue);
  if (logger_queue == NULL) {
      app_log_error("Error from xQueueCreate");
      reset_on_fatal_error();
  }

  xHandle = xTaskCreateStatic(logger_code,
                              "logger",
                              TASK_STACK_SIZE,
                              NULL,
                              TASK_PRIORITY,
                              xStack,
                              &xTaskBuffer);
  if (xHandle == NULL) {
      app_log_error("NULL returned by xTaskCreateStatic\n");
      reset_on_fatal_error();
  }

}

// log must point to a string with a maximum of LOG_MAX_LENGTH characters,
// not including the final '\0'.
// A final '\n' is added by the logger.
void logger_log(char *log) {

  uint8_t l;
  logger_message_t logger_message;
  BaseType_t os_rs;

  // First, get a time stamp.
  logger_message.time_stamp = xTaskGetTickCountFromISR();

  // LOG_MAX_LENGTH is supposed to be less than or equal to 255.
  l = strlen(log) + 1;    // l includes final '\0'.
  if (l > LOG_MAX_LENGTH + 1) {
      l = LOG_MAX_LENGTH + 1;
  }
  memcpy(logger_message.log, log, l);
  // Ensure we always have a final '\0'.
  logger_message.log[LOG_MAX_LENGTH] = '\0';

  // xQueueSendToBack makes a copy of the message. So, no problem for
  // logger_message in being local (.i.e. in automatic storage).
  os_rs = xQueueSendToBack(logger_queue, &logger_message, 0);
  if (os_rs == errQUEUE_FULL) {
      app_log_warning("Logger queue full\n");
  }

}
