/*
 * API_debounce.h
 *
 *  Created on: Nov 13, 2023
 *      Author: igpollitzer
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>
#include <stdbool.h>

void debounceFSM_init();		// Inicializa la maquina de estados
void debounceFSM_update();  	// Verifica la situacion de la maquina y actua en caso de necesidad
bool_t readKey();               // Retorna verdadero o falso, si se oprimio el boton.

#endif /* API_INC_API_DEBOUNCE_H_ */
