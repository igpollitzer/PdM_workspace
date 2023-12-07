/*
 * API_gps.c
 *
 *  Created on: Dec 7, 2023
 *      Author: igpollitzer
 */

/*
static struct gpsData{
	char Latitude[] =   "LAT:    .       ";
	char Longitude[] =  "LON:    .       ";
	char Satellites[] = "Satellites:     ";
	char Error[] =      "Error:  .  x25m ";
	char Time[] =       "Time:    :      ";
	char Date[] =       "Date:    /  /   ";
};

void gpsParse(char* parseLine){
	if (parseLine[4] == 'G'){
		if (parseline[19] == ','){
			gpsData.Latitude[6] = 'X';
			gpsData.Latitude[7] = 'X';
			gpsData.Latitude[9] = 'X';
			gpsData.Latitude[10] = 'X';
			gpsData.Latitude[11] = 'X';
			gpsData.Latitude[12] = 'X';
			gpsData.Latitude[13] = 'X';
			gpsData.Longitude[5] = 'X';
			gpsData.Longitude[6] = 'X';
			gpsData.Longitude[7] = 'X';
			gpsData.Longitude[9] = 'X';
			gpsData.Longitude[10] = 'X';
			gpsData.Longitude[11] = 'X';
			gpsData.Longitude[12] = 'X';
			gpsData.Longitude[13] = 'X';
			gpsData.Longitude[15] = 'X';
			gpsData.Satellites[13] = 'X';
			gpsData.Satellites[14] = 'X';
			gpsData.Error[7] = 'X';
			gpsData.Error[9] = 'X';
			gpsData.Error[10] = 'X';
		}
		else{
			gpsData.Latitude[6] = parseLine[17];
			gpsData.Latitude[7] = parseLine[18];
			gpsData.Latitude[9] = parseLine[19];
			gpsData.Latitude[10] = parseLine[20];
			gpsData.Latitude[11] = parseLine[22];
			gpsData.Latitude[12] = parseLine[23];
			gpsData.Latitude[13] = parseLine[24];
			gpsData.Longitude[5] = parseLine[30];
			gpsData.Longitude[6] = parseLine[31];
			gpsData.Longitude[7] = parseLine[32];
			gpsData.Longitude[9] = parseLine[33];
			gpsData.Longitude[10] = parseLine[34];
			gpsData.Longitude[11] = parseLine[36];
			gpsData.Longitude[12] = parseLine[37];
			gpsData.Longitude[13] = parseLine[38];
			gpsData.Longitude[15] = parseLine[42];
			gpsData.Satellites[13] = parseLine[46];
			gpsData.Satellites[14] = parseLine[47];
			gpsData.Error[7] = parseLine[49];
			gpsData.Error[9] = parseLine[51];
			gpsData.Error[10] = parseLine[52];
		}
	}
	if(parseLine[4] == 'M'){
		if (parseline[19] == ','){
			gpsData.Time[7] = 'X';
			gpsData.Time[8] = 'X';
			gpsData.Time[10] = 'X';
			gpsData.Time[11] = 'X';
			gpsData.Time[13] = 'X';
			gpsData.Time[14] = 'X';
			gpsData.Date[7] = 'X';
			gpsData.Date[8] = 'X';
			gpsData.Date[10] = 'X';
			gpsData.Date[11] = 'X';
			gpsData.Date[13] = 'X';
			gpsData.Date[14] = 'X';
		}
		else{
			gpsData.Time[7] = parseLine[7];
			gpsData.Time[8] = parseLine[8];
			gpsData.Time[10] = parseLine[9];
			gpsData.Time[11] = parseLine[10];
			gpsData.Time[13] = parseLine[11];
			gpsData.Time[14] = parseLine[12];
			gpsData.Date[7] = parseLine[53];
			gpsData.Date[8] = parseLine[54];
			gpsData.Date[10] = parseLine[55];
			gpsData.Date[11] = parseLine[56];
			gpsData.Date[13] = parseLine[57];
			gpsData.Date[14] = parseLine[58];
		}
	}
}

*/
