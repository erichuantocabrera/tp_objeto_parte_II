#ifndef FUNCIONES_EXTRAS_H_
#define FUNCIONES_EXTRAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <commons/error.h>
#include <commons/config.h>
#include <commons/log.h>
#include <commons/collections/list.h>

typedef struct
{
	int PUERTO_ESCUCHA;
	int TAMANIO;
	int TAMANIO_PAGINA;
	char* TIPO_ASIGNACION;
	char* ALGORITMO_REEMPLAZO_MMU;
	int MARCOS_POR_CARPINCHO;
	int CANTIDAD_ENTRADAS_TLB;
	char* ALGORITMO_REEMPLAZO_TLB;
	int RETARDO_ACIERTO_TLB;
	int RETARDO_FALLO_TLB;
	char* PATH_DUMP_TLB;
} t_config_memoria;

typedef struct {
	void* inicio;
	uint32_t num_marco;
	uint32_t pid;
	uint32_t num_pagina;
	bool esta_libre;
//	void* final;
} t_marco;

typedef struct {
	uint32_t num_pagina;
	uint32_t marco_asignado;
	bool esta_presente;//si esta o no en memoria
	bool esta_modificado;//pf
} t_pagina;

typedef struct {
	uint32_t prevAlloc;
	uint32_t nextAlloc;
	uint8_t isFree;
} t_heap_metadata;

typedef struct {
	uint32_t pid;
	t_list* tabla_de_paginas; //una lista de  --> t_paginas
} t_proceso;


t_config_memoria* CONFIG_MEMORIA; //para tener todos los datos de la config
t_log* LOGGER;
void* MI_MEMORIA;
t_list* TABLA_DE_MARCOS; //para facilitar el encuentro de marcos libres y para el envio de marcos al disco
t_list* TABLA_GENERAL; //tabla_general a la que se debe ir abuscar cuando no se encuentre en la TLB


void iniciar_memoria();


#endif /* FUNCIONES_EXTRAS_H_ */
