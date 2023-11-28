/*
 * API_uart.c
 *
 *  Created on: Nov 27, 2023
 *      Author: igpollitzer
 */

#include "API_uart.h"

static char uartPort_d[] = "Port = USART3\n\r";
static char baudRate_d[] = "Baud Rate = 115200\n\r";
static char wordLength_d[] = "Word Length = 8\n\r";
static char stopBits_d[] = "Stop Bits = 1\n\r";
static char parity_d[] = "Parity Bit = None\n\r";
static char mode_d[] = "Mode = Tx Rx\n\r";
static char hwFlowCtl_d[] = "Hardware Flow Control = None\n\r";
static char overSampling_d[] = "Over Sampling = 16\n\r";

static UART_HandleTypeDef huart3;

bool_t uartInit(void){
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK){
        return API_UART_INIT_ERROR;
    }
    else{
    	HAL_UART_Transmit(&huart3, uartPort_d, sizeof(uartPort_d), HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart3, baudRate_d, sizeof(baudRate_d), HAL_MAX_DELAY);
	    HAL_UART_Transmit(&huart3, wordLength_d, sizeof(wordLength_d), HAL_MAX_DELAY);
	    HAL_UART_Transmit(&huart3, stopBits_d, sizeof(stopBits_d), HAL_MAX_DELAY);
	    HAL_UART_Transmit(&huart3, parity_d, sizeof(parity_d), HAL_MAX_DELAY);
	    HAL_UART_Transmit(&huart3, mode_d, sizeof(mode_d), HAL_MAX_DELAY);
	    HAL_UART_Transmit(&huart3, hwFlowCtl_d, sizeof(hwFlowCtl_d), HAL_MAX_DELAY);
        HAL_UART_Transmit(&huart3, overSampling_d, sizeof(overSampling_d), HAL_MAX_DELAY);
    }
    return API_UART_INIT_OK;
}

void uartSendString(uint8_t* pstring){
	HAL_UART_Transmit(&huart3, pstring, sizeof(pstring), HAL_MAX_DELAY);
}

void uartSendStringSize(uint8_t* pstring, uint16_t size){
	HAL_UART_Transmit(&huart3, pstring, size, HAL_MAX_DELAY);

}

void uartReceiveStringSize(uint8_t* pstring, uint16_t size){
	HAL_UART_Receive(&huart3, pstring, size, HAL_MAX_DELAY);
}
