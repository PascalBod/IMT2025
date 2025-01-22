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

#include <stdio.h>

#include "app_log.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "logger.h"
#include "utils.h"

#define QUEUE_LENGTH    5
#define QUEUE_ITEM_WAIT_PERIOD_MS   10000

#define SHORT_PERIOD_MS 800
#define LONG_PERIOD_MS  1100

#define PRODUCER_1_ID   1
#define PRODUCER_2_ID   2

#define TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define TASK_PRIORITY   10

typedef struct {
  uint8_t producer_id;
  uint32_t counter;
} message_t;

typedef struct {
  uint8_t producer_id;
  uint32_t period_ms;
} task_args_t;

static QueueHandle_t queue;

static StaticTask_t xTaskBuffer_1;
static StaticTask_t xTaskBuffer_2;
static StaticTask_t xTaskBuffer_3;

static StackType_t  xStack_1[TASK_STACK_SIZE];
static StackType_t  xStack_2[TASK_STACK_SIZE];
static StackType_t  xStack_3[TASK_STACK_SIZE];

static StaticQueue_t xQueue;
static uint8_t xQueueStorage[QUEUE_LENGTH * sizeof(message_t)];

static task_args_t producer_1_args;
static task_args_t producer_2_args;

static void producer_code(void *pvParameters) {

  task_args_t *task_args;
  message_t message;
  uint32_t counter = 0;
  BaseType_t os_rs;
  char log[LOG_MAX_LENGTH + 1];

  task_args = (task_args_t *)pvParameters;

  snprintf(log, LOG_MAX_LENGTH + 1, "Producer %u started",
           task_args->producer_id);
  logger_log(log);

  message.producer_id = task_args->producer_id;

  while (true) {
      message.counter = counter;
      snprintf(log, LOG_MAX_LENGTH + 1, "Producer %u - Writing %lu into queue",
               task_args->producer_id, counter);
      logger_log(log);
      os_rs = xQueueSendToBack(queue, &message, 0);
      if (os_rs == errQUEUE_FULL) {
          snprintf(log, LOG_MAX_LENGTH + 1,
                   "Producer %u - Queue full, counter lost",
                   task_args->producer_id);
          logger_log(log);
      }
      counter++;
      vTaskDelay(pdMS_TO_TICKS(task_args->period_ms));
  }

}

static void consumer_code(void *pvParameters) {

  (void)pvParameters;

  message_t message;
  BaseType_t os_rs;
  char log[LOG_MAX_LENGTH + 1];

  snprintf(log, LOG_MAX_LENGTH + 1, "Consumer started");
  logger_log(log);

  while (true) {
      // We could use an infinite timeout, i.e. no timeout. But using a finite
      // value allows for liveliness checking when no message is received
      // for a long period.
      os_rs = xQueueReceive(queue, &message, QUEUE_ITEM_WAIT_PERIOD_MS);
      if (os_rs == pdFALSE) {
          snprintf(log, LOG_MAX_LENGTH + 1, "Consumer - Queue empty");
          logger_log(log);
          continue;
      }
      snprintf(log, LOG_MAX_LENGTH + 1, "Consumer - Received %lu from %u",
               message.counter, message.producer_id);
      logger_log(log);
  }

}

void cons_prod_init(void)
{

  TaskHandle_t xHandle;

  // Create the queue. Important: must be created before creating
  // the tasks.
  queue = xQueueCreateStatic(QUEUE_LENGTH, sizeof(message_t),
                             xQueueStorage, &xQueue);
  if (queue == NULL) {
      app_log_error("Error from xQueueCreate");
      reset_on_fatal_error();
  }

  producer_1_args.producer_id = PRODUCER_1_ID;
  producer_1_args.period_ms = SHORT_PERIOD_MS;

  xHandle = xTaskCreateStatic(producer_code,
                              "producer1",
                              TASK_STACK_SIZE,
                              &producer_1_args,
                              TASK_PRIORITY,
                              xStack_1,
                              &xTaskBuffer_1);
  if (xHandle == NULL) {
      app_log_error("NULL returned by xTaskCreateStatic\n");
      reset_on_fatal_error();
  }

  producer_2_args.producer_id = PRODUCER_2_ID;
  producer_2_args.period_ms = LONG_PERIOD_MS;

  xHandle = xTaskCreateStatic(producer_code,
                              "producer2",
                              TASK_STACK_SIZE,
                              &producer_2_args,
                              TASK_PRIORITY,
                              xStack_2,
                              &xTaskBuffer_2);
  if (xHandle == NULL) {
      app_log_error("NULL returned by xTaskCreateStatic\n");
      reset_on_fatal_error();
  }

  xHandle = xTaskCreateStatic(consumer_code,
                              "consumer",
                              TASK_STACK_SIZE,
                              NULL,
                              TASK_PRIORITY,
                              xStack_3,
                              &xTaskBuffer_3);
  if (xHandle == NULL) {
      app_log_error("NULL returned by xTaskCreateStatic\n");
      reset_on_fatal_error();
  }

}
