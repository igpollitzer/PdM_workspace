/*
 * API_i2c.c
 *
 *  Created on: Dec 8, 2023
 *      Author: igpollitzer
 */

#include "API_i2c.h"

void lcdSendCommand(char command){
  char data_msb, data_lsb;
	uint8_t data[4];
	//Estoy trabajando en modo de 4 bits, tengo que separar el comando en 2 partes: msb y lsb
	data_msb = (command & 0xf0);
	data_lsb = ((command << 4) & 0xf0);
	data[0] = data_msb | 0x0C;  // Subo el Enable
	data[1] = data_msb | 0x08;  // Bajo el Enable, para que lea la mitad alta
	data[2] = data_lsb | 0x0C;  // Subo el Enable
	data[3] = data_lsb | 0x08;  // Bajo el Enable, para que lea la mitad baja
	HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDRESS,(uint8_t*) data, 4, 100);
}

void lcdInit(void){
	// Los delays son mayores que los pedidos en la hoja de datos.
	HAL_Delay(50);
	lcdSendCommand(0x30); // Function set
	HAL_Delay(10);
	lcdSendCommand(0x28); // Function set: 2 lineas, caracteres 8x5
	HAL_Delay(10);
	lcdSendCommand(0x28); // Function set
	HAL_Delay(10);
	lcdSendCommand(0x0C); // Display ON/OFF control: Display encendido
	HAL_Delay(10);
	lcdSendCommand(0x01); // Display Clear
	HAL_Delay(10);
	lcdSendCommand(0x06); // Entry Mode Set: De derecha a izquierda
	HAL_Delay(10);
	lcdSendCommand(0x02); // Return Home
	HAL_Delay(10);
}

void lcdSendText(char text){
	char data_msb, data_lsb;
	uint8_t data[4];
	//Estoy trabajando en modo de 4 bits, tengo que separar el comando en 2 partes: msb y lsb
	data_msb = (text & 0xf0);
	data_lsb = ((text << 4) & 0xf0);
	data[0] = data_msb | 0x0D;  // Subo el Enable
	data[1] = data_msb | 0x09;  // Bajo el Enable, para que lea la mitad alta
	data[2] = data_lsb | 0x0D;  // Subo el Enable
	data[3] = data_lsb | 0x09;  // Bajo el Enable, para que lea la mitad baja
	HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDRESS,(uint8_t*) data, 4, 100);
}

void lcdSendString(char* text, uint8_t length){
    for (uint8_t i = 0 ; i < length ; i++){
    	lcdSendText(text[i]);
    }
}

void lcdLineOne(void){
	lcdSendCommand(0x80);
}

void lcdLineTwo(void){
	lcdSendCommand(0xC0);
}
