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
    RTOS for ML presentation - solution to exercise 05 step 2.
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

#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"

// Define UART pins.
#define UART_TX_PORT gpioPortA
#define UART_TX_PIN  5
#define UART_RX_PORT gpioPortA
#define UART_RX_PIN  6

// Set UART initialization block content to default values.
static USART_InitAsync_TypeDef usart_init = USART_INITASYNC_DEFAULT;

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{

  // Enable required clocks: for USART0 block and for GPIO block.
  // The EFR32BG24 has only one USART, named USART0.
  CMU_ClockEnable(cmuClock_USART0, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Initialize GPIO pins used by USART0.
  // See section 24.3.1 of the Reference Manual.
  // Out argument (the 4th one) is not used, for gpioModePushPull.
  GPIO_PinModeSet(UART_TX_PORT, UART_TX_PIN, gpioModePushPull, 1);
  // Out argument (the 4th one): no filter.
  GPIO_PinModeSet(UART_RX_PORT, UART_RX_PIN, gpioModeInput, 0);

  // Route USART0 pins to GPIO pins.
  // See section 24.6.173 of the Reference Manual.
  GPIO->USARTROUTE[0].TXROUTE = (UART_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) |
      (UART_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].RXROUTE = (UART_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT) |
      (UART_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);

  // Now, enable the routes.
  // See section 24.6.167 of the Reference Manual.
  GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;

  // Initialize USART0. USART_INITASYNC_DEFAULT uses the following
  // characteristics:
  // - speed: 115200 b/s
  // - data bits: 8
  // - parity: none
  // - stop bits: 1
  // - no hardware flow control
  // Modifying a characteristic is done with a simple assignment. For instance,
  // to set speed to 9600 b/s:
  // usart_init.baudrate = 9600;
  USART_InitAsync(USART0, &usart_init);

}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{

  uint32_t usart_status;
  uint8_t rec_byte;

  usart_status = USART_StatusGet(USART0);
  if ((usart_status & USART_STATUS_RXDATAV) != 0) {
      // One byte received, get it.
      rec_byte = USART_RxDataGet(USART0);
      // And echo it.
      USART_Tx(USART0, rec_byte);
  }

  // Another way to echo a byte is to use USART_Rx, as below. But USART_Rx
  // blocks until a byte is received. Consequently, it's not possible to run
  // some other code while waiting for a byte.
  //
  // rec_byte = USART_Rx(USART0);
  // USART_Tx(USART0, rec_byte);

}
