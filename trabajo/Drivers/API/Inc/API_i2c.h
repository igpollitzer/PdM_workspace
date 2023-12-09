/*
 * API_i2c.h
 *
 *  Created on: Dec 8, 2023
 *      Author: igpollitzer
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

#define LCD_ADDRESS 0x4E
#define LCD_LENGTH 16

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c2;

/**
  * @brief Funcion de incializacion del LCD
  * @param None
  * @retval None
  */
void lcdInit(void);

/**
  * @brief Envio de comandos al LCD
  * @param Instruccion a enviar
  * @retval None
  */
void lcdSendCommand(char);

/**
  * @brief Envio de caracter para mostrar en pantalla
  * @param Caracter a mostrar
  * @retval None
  */
void lcdSendText(char);

/**
  * @brief Funcion para mostrar una cadena de caracteres en el LCD
  * @param Cadena de caracteres
  * @param Cantidad de caracteres
  * @retval None
  */
void lcdSendString(char*, uint8_t);

/**
  * @brief Funcion para ubicar el cursor en el comienzo de la hilera superior
  * @param None
  * @retval None
  */
void lcdLineOne(void);

/**
  * @brief Funcion para ubicar el cursor en el comienzo de la hilera inferior
  * @param None
  * @retval None
  */
void lcdLineTwo(void);

#endif /* API_INC_API_I2C_H_ */
