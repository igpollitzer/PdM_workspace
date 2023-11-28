/*
 * API_debounce.c
 *
 *  Created on: Nov 13, 2023
 *      Author: igpollitzer
 */

#include "API_delay.h"      // necesito el delay, para el rebote
#include "API_debounce.h"
#include "stm32f4xx_hal.h"  // necesito el HAL, para leer los pines
#include "main.h"           // necesito el main, para tomar el nombre del boton

typedef enum{
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RISING,
    } debounceState_t;

static debounceState_t estado = BUTTON_UP;
static uint32_t espera = 40;
static delay_t rebote = {.startTime = 0,
                        .duration = 0,
                        .running = false};

// Booleanos de disparo y soltado, para saber cuando occurieron eventos
static bool_t disparo = false;
static bool_t soltado = false;

// debounceFSM_init inicializa la maquina de estados, como en su declaracion

void debounceFSM_init(){
    estado = BUTTON_UP;
}

/* debounceFSM_update es una maquina de estados que contiene los 2 casos de estados de accion del boton
 * presionado (BUTTON_DOWN) y suelto (BUTTON_UP), y los 2 casos de transicion ascendente (BUTTON RISING)
 * y descendente (BUTTON FALLING), y las condiciones de paso entre ellos.
 * Si se confirma la activacion del boton, se levanta la bandera de disparo.
 */

void debounceFSM_update(){
	switch (estado){
	case BUTTON_UP:
		if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET){
            estado = BUTTON_FALLING;
			delayInit(&rebote, espera);
			delayRead(&rebote);
		}
		break;
	case BUTTON_FALLING:
		if(delayRead(&rebote)){
    		if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET){
    			estado = BUTTON_DOWN;
    		    disparo = true;
    		}
    		else if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_RESET){
	    		estado = BUTTON_UP;
    		}
		}
		break;
	case BUTTON_DOWN:
		if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_RESET){
            estado = BUTTON_RISING;
			delayInit(&rebote, espera);
			delayRead(&rebote);
		}
		break;
	case BUTTON_RISING:
		if(delayRead(&rebote)){
    		if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET){
    			estado = BUTTON_DOWN;
    		}
    		else if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_RESET){
	    		estado = BUTTON_UP;
	    		soltado = true;
    		}
		}
	default:
	}
}

/* readKey lee la bandera que activa el oprimir el boton. Si es verdadero, reinicia la variable
 * y retorna verdadero. Caso contrario, retorna falso.
 */
bool_t readKey(){
	if(disparo == true){
		disparo = false;
		return true;
	}
	else{
		return false;
	}
}

// La funcion wasKeyReleased es como readKey, pero para detectar si se solto el boton.
bool_t wasKeyReleased(){
	if(soltado == true){
		soltado = false;
		return true;
	}
	else{
		return false;
	}
}
