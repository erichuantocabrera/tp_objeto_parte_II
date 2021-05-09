#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <pthread.h>

// inicializa las variables que se toman por archivo de configuracion
void iniciar_variables();
// inicializacion
void inicializar_memoria();
//finaliza variables creadas
void finalizar_variables();


#endif /* FUNCIONES_H_ */
