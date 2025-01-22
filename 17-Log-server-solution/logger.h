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

#ifndef LOGGER_H_
#define LOGGER_H_

#include "FreeRTOS.h"
#include "queue.h"

// LOG_MAX_LENGTH must be less than or equal to 255, as we use a uint8_t
// in logger_log to store log line length.
#define LOG_MAX_LENGTH 40

extern QueueHandle_t logger_queue;

typedef struct {
  TickType_t time_stamp;
  char log[LOG_MAX_LENGTH + 1];
} logger_message_t;

void logger_init(void);

// log must point to a string with a maximum of LOG_MAX_LENGTH characters,
// not including the final '\0'.
// A final '\n' is added by the logger.
void logger_log(char *log);

#endif /* LOGGER_H_ */
