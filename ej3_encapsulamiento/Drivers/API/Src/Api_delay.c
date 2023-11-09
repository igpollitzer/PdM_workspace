/*
 * Api_delay.c
 *
 *  Created on: Nov 2, 2023
 *      Author: igpollitzer
 */

#include "API_delay.h"
#include "stm32f4xx_hal.h"

void delayInit( delay_t * delay, tick_t duration ){
    delay->duration = duration;
    delay->running = false;
}

bool_t delayRead( delay_t * delay ){
	if (delay->running == false){
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}else{
		// Calculo si paso el tiempo del delay
		if (HAL_GetTick() - delay->startTime > delay->duration){
			delay->running = false;
			return true;
		}
	}
	return false;
}
void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration = duration;
}
