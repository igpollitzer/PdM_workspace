/*
 * API_gps.h
 *
 *  Created on: Dec 7, 2023
 *      Author: igpollitzer
 */

#ifndef API_INC_API_GPS_H_
#define API_INC_API_GPS_H_

#include "stm32f4xx_hal.h"

#define MAX_NMEA_LENGTH 82

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

/**
  * @brief Funcion de actualizacion de la informacion del GPS
  * @param None
  * @retval None
  */
void gpsUpdate(void);

/**
  * @brief Parseo de la linea RMC
  * @param None
  * @retval None
  */
void parseRMC(void);

/**
  * @brief Parseo de la linea GGA
  * @param None
  * @retval None
  */
void parseGGA(void);

/**
  * @brief Toma de los datos, la informacion de la latitud
  * @param None
  * @retval Cadena de caracteres con la latitud
  */
char* gpsLatitude(void);

/**
  * @brief Toma de los datos, la informacion de la longitud
  * @param None
  * @retval Cadena de caracteres con la longitud
  */
char* gpsLongitude(void);

/**
  * @brief Toma de los datos, la informacion de lao satelites
  * @param None
  * @retval Cadena de caracteres con la cantidad de satelites
  */
char* gpsSatellites(void);

/**
  * @brief Toma de los datos, la informacion del error
  * @param None
  * @retval Cadena de caracteres con el error
  */
char* gpsError(void);

/**
  * @brief Toma de los datos, la informacion del tiempo
  * @param None
  * @retval Cadena de caracteres con el tiempo
  */
char* gpsTime(void);

/**
  * @brief Toma de los datos, la informacion de la fecha
  * @param None
  * @retval Cadena de caracteres con la fecha
  */
char* gpsDate(void);

#endif /* API_INC_API_GPS_H_ */
