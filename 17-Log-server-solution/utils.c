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

#include "app_log.h"
#include "sl_udelay.h"

// Maximum delay for sl_udelay_wait: 100000 µs.
#define RESET_DELAY_US  100000

void reset_on_fatal_error(void) {

  app_log_error("About to reset\n");
  sl_udelay_wait(RESET_DELAY_US);
  NVIC_SystemReset();

}