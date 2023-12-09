/*
 * API_gps.c
 *
 *  Created on: Dec 7, 2023
 *      Author: igpollitzer
 */

#include"API_gps.h"

uint8_t i = 0;
char gpsData[1] = "";

char parseLine[MAX_NMEA_LENGTH] = "";
char latitude[] = "LAT:            ";
char longitude[] = "LON:            ";
char satellites[] = "Satellites:     ";
char error[] = "Error:          ";
char time[] = "Time:           ";
char date[] = "Date:           ";


void gpsUpdate(void){
    // Este while 1 es para que agrupe todas las lineas que manda el GPS. La ultima es la de GLL.
	while(1){
		HAL_UART_Receive(&huart2, ((uint8_t*) gpsData), 1, HAL_MAX_DELAY);
		/*
		 * El parseo de la informacion del gps es el siguiente:
		 * Las lineas empiezan con un $ y terminan en /n
		 * La informacion la tomo de las lineas de GPRMC y GPGGA
		 * La linea de GLL es la ultima. Uso esa para salir.
		 */

		if (gpsData[0] == '$'){
			i = 0;
			while(gpsData[0] != '\n'){
				parseLine[i] = gpsData[0];
				HAL_UART_Receive(&huart2, ((uint8_t*) gpsData), 1, HAL_MAX_DELAY);
				i++;
			}
			parseLine[i] = gpsData[0];
			if(parseLine[3] == 'R' && parseLine[4] == 'M' && parseLine[5] == 'C'){
				parseRMC();
			}
			if(parseLine[3] == 'G' && parseLine[4] == 'G' && parseLine[5] == 'A'){
				parseGGA();
			}
			if(parseLine[3] == 'G' && parseLine[4] == 'L' && parseLine[5] == 'L'){
				break;
			}

		}
	}
}

void parseRMC(void){
//	if (parseLine[20] == ','){
	if (i < 50){
		date[7] = ' ';
		date[8] = ' ';
		date[9] = 'N';
		date[10] = 'O';
		date[11] = ' ';
		date[12] = ' ';
		date[13] = ' ';
		date[14] = ' ';
		time[7] = ' ';
		time[8] = 'D';
		time[9] = 'A';
		time[10] = 'T';
		time[11] = 'A';
		time[12] = ' ';
		time[13] = ' ';
		time[14] = ' ';
	}
	else{
		time[7] = parseLine[7];
		time[8] = parseLine[8];
		time[9] = ':';
		time[10] = parseLine[9];
		time[11] = parseLine[10];
		time[12] = ':';
		time[13] = parseLine[11];
		time[14] = parseLine[12];
		date[7] = parseLine[53];
		date[8] = parseLine[54];
		date[9] = '/';
		date[10] = parseLine[55];
		date[11] = parseLine[56];
		date[12] = '/';
		date[13] = parseLine[57];
		date[14] = parseLine[58];
	}
}

void parseGGA(void){
//	if (parseLine[18] == ','){
	if (i < 50){
		latitude[6] = ' ';
		latitude[7] = ' ';
		latitude[8] = ' ';
		latitude[9] = 'N';
		latitude[10] = 'O';
		latitude[11] = ' ';
		latitude[12] = ' ';
		latitude[13] = ' ';
		latitude[15] = ' ';
		longitude[5] = ' ';
		longitude[6] = ' ';
		longitude[7] = ' ';
		longitude[8] = 'D';
		longitude[9] = 'A';
		longitude[10] = 'T';
		longitude[11] = 'A';
		longitude[12] = ' ';
		longitude[13] = ' ';
		longitude[15] = ' ';
		satellites[13] = 'N';
		satellites[14] = 'O';
		error[7] = ' ';
		error[8] = ' ';
		error[9] = ' ';
		error[10] = ' ';
		error[11] = 'D';
		error[12] = 'A';
		error[13] = 'T';
		error[14] = 'A';
	}
	else{
		latitude[6] = parseLine[17];
		latitude[7] = parseLine[18];
		latitude[8] = '.';
		latitude[9] = parseLine[19];
		latitude[10] = parseLine[20];
		latitude[11] = parseLine[22];
		latitude[12] = parseLine[23];
		latitude[13] = parseLine[24];
		latitude[15] = parseLine[28];
		if (parseLine[30] == '1'){
			longitude[5] = parseLine[30];
		}
		else{
			longitude[5] = ' ';
		}
		longitude[6] = parseLine[31];
		longitude[7] = parseLine[32];
		longitude[8] = '.';
		longitude[9] = parseLine[33];
		longitude[10] = parseLine[34];
		longitude[11] = parseLine[36];
		longitude[12] = parseLine[37];
		longitude[13] = parseLine[38];
		longitude[15] = parseLine[42];
		satellites[13] = parseLine[46];
		satellites[14] = parseLine[47];
		error[7] = parseLine[49];
		error[8] = '.';
		error[9] = parseLine[51];
		error[10] = parseLine[52];
		error[11] = 'x';
		error[12] = '2';
		error[13] = '5';
		error[14] = 'm';
	}
}

char* gpsLatitude(void){
	return latitude;
}

char* gpsLongitude(void){
	return longitude;
}

char* gpsSatellites(void){
	return satellites;
}

char* gpsError(void){
	return error;
}

char* gpsTime(void){
	return time;
}

char* gpsDate(){
	return date;
}
