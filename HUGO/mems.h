#ifndef MEMS_H_
#define MEMS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include "funciones_extras.h"

typedef enum {
	_start_process,
	_reserve_memory,
	_free_memory,
	_read_memory,
	_write_memory
}code_error_mems;

void start_process(int pid);
int reserve_memory(int pid, int size);

/*
 int memfree(alloc* porcion_memoria);
uint32_t obtener_ultimo_prevAlloc_libre(heapMetadata *heapMetadata);
uint32_t obtener_ultimo_nextAlloc_libre(heapMetadata *heapMetadata);
heapMetadata* obtener_heap_metadata(uint32_t allocPos);
void* algoritmo_primer_ajuste(t_list* lista, int tamanio_a_guardar, int* pos, int* sobrante);
void* crear_alloc(ultimo,size);
 */

#endif /* MEMS_H_ */
