/*
 * API_uart.h
 *
 *  Created on: Nov 27, 2023
 *      Author: igpollitzer
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#define API_UART_INIT_OK true
#define API_UART_INIT_ERROR true

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

//#include "stm32f4xx_hal_def.h"
//#include "stm32f4xx_hal_uart.h"

typedef bool bool_t;

bool_t uartInit(void);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
