#include "mems.h"

char* traduccion(int numero)
{
	char* mensaje = NULL;

	switch (numero){
		case _start_process:
			mensaje = string_duplicate("start_process");
			break;

		case _reserve_memory:
			mensaje = string_duplicate("reserve_memory");
			break;

		case _free_memory:
			mensaje = string_duplicate("free_memory_");
			break;

		case _read_memory:
			mensaje = string_duplicate("read_memory_");
			break;

		case _write_memory:
			mensaje = string_duplicate("write_memory_");
			break;
	}

	return mensaje;
}

void error_mems(int nivel, char* funcion_afectada, char* detalle)
{

	char* palabra1 = traduccion(nivel);

	error_show("error en: \"%s\" funcion: \"%s\" \nproblema: \"%s\"  \n", palabra1, funcion_afectada, detalle);

	free(palabra1);
	//exit(1);
}

t_proceso* buscar_proceso(int pid)
{
	bool funcionn(void* el_pid)
	{
		return (pid==(*(int*)el_pid))? true: false;
	}

	t_proceso* proceso = list_find(TABLA_GENERAL, funcionn);

	return proceso;
}

t_proceso* crear_proceso(int pid)
{
	t_proceso* proceso = malloc(sizeof(t_proceso));

	proceso->pid = pid;
	proceso->tabla_de_paginas = list_create();

	return proceso;
}

t_pagina* create_pagina(int num_pagina, int num_marco, bool presente, bool modificado)
{
	t_pagina* pagina = malloc(sizeof(t_pagina));

	pagina->num_pagina = num_pagina;
	pagina->marco_asignado = num_marco;
	pagina->esta_presente = presente;
	pagina->esta_modificado = modificado;

	return pagina;
}

t_heap_metadata* create_heap_metadata(int direccion_anterior, int direccion_siguiente)
{
	t_heap_metadata* heap_metadata = malloc(sizeof(t_heap_metadata));

	heap_metadata->prevAlloc = direccion_anterior;
	heap_metadata->nextAlloc = direccion_siguiente;
	heap_metadata->isFree = true;

	return heap_metadata;
}

void* siguiente_direccion(t_proceso* proceso)
{
	int direccion_fisica = NULL;
	int offset = 0;

	if(string_equals_ignore_case(CONFIG_MEMORIA->TIPO_ASIGNACION, "FIJA"))
	{
		if(hay_pagina_vacia(proceso->tabla_de_paginas))
		{
			t_pagina* pagina = buscar_pagina_vacia(proceso->tabla_de_paginas);
			direccion_fisica = pagina->marco_asignado * CONFIG_MEMORIA->TAMANIO_PAGINA + offset;
		}

	}

	direccion_fisica = (((t_marco*)asignar_marco(proceso))->num_marco) * CONFIG_MEMORIA->TAMANIO_PAGINA + offset;

	return MI_MEMORIA + direccion_fisica;
}

void asignar_primer_heapmetadata(t_proceso* proceso)
{
	t_heap_metadata* el_heap = create_heap_metadata(0, 0);
	int direccion_fisica = ((t_marco*)list_get(proceso->tabla_de_paginas, 0))->inicio;
	int espacio_disponible = CONFIG_MEMORIA->TAMANIO_PAGINA;
	int tam_heap_metadata = sizeof(t_heap_metadata);
	int aux = 0;

	while(tam_heap_metadata > espacio_disponible)
	{
		memcpy(direccion_fisica, el_heap + aux, espacio_disponible);
		tam_heap_metadata = tam_heap_metadata - espacio_disponible;
		direccion_fisica = siguiente_direccion(proceso);
		aux = aux + espacio_disponible;
	}

	memcpy(direccion_fisica, el_heap + aux, tam_heap_metadata);

}

bool hay_marco_libre(t_marco* marco)
{
	return marco!=NULL;
}

bool no_hay_marco_libre(t_marco* marco)
{
	return marco==NULL;
}


t_marco* buscar_marco_libre_en_ram(t_proceso* proceso) //revisar si asi funcionaba esto de usar funciones de listas.
{
	bool funcionn(void* marco_X)
	{
		if(((t_marco*)(marco_X))->esta_libre == true)
			return true;

		return false;
	}

	t_marco* marco = list_find(TABLA_DE_MARCOS, &funcionn);

	if(marco==NULL) return NULL;

	marco->pid = proceso->pid;
	marco->num_pagina = list_size(proceso->tabla_de_paginas);
	marco->esta_libre = false;

	return marco;
}
t_marco* swap_out(t_proceso* proceso)
{
	if(string_equals_ignore_case(CONFIG_MEMORIA->TIPO_ASIGNACION, "FIJA"))
	{
		//despues ver si lo buscamos en su tabla de paginas o directamente en la tabla de marcos
		t_pagina* pagina = seleccionar_pagina_a_enviar(proceso->tabla_de_paginas);

		enviar_marco_a_disco(proceso->pid, pagina->num_pagina, pagina->marco_asignado);

		pagina->esta_presente = false;

		t_pagina* pagina_nueva = create_pagina(list_size(proceso->tabla_de_paginas), pagina->marco_asignado, true, false);

		list_add(proceso->tabla_de_paginas, pagina_nueva);

	}

	if(string_equals_ignore_case(CONFIG_MEMORIA->TIPO_ASIGNACION, "DINAMICA"))
	{
		//if(string_equals_ignore_case(-, "LOCAL")) la asignacion dinamica puede ser tanto
		//if(string_equals_ignore_case(-, "GLOBAL")) local como global.
		t_marco* marco = seleccionar_marco_a_enviar();//se le envia TABLADEMARCOS

		enviar_n_bytes_a_disco(marco->pid, marco->num_pagina, marco->inicio);

		t_pagina* pagina = list_get((t_proceso*)(buscar_proceso(marco->pid))->tabla_de_paginas, marco->num_pagina);

		pagina->esta_presente = false;

		t_pagina* pagina_nueva = create_pagina(list_size(proceso->tabla_de_paginas), pagina->marco_asignado, true, false);

		list_add(proceso->tabla_de_paginas, pagina_nueva);
	}
}

t_marco* asignar_marco(t_proceso* proceso)
{
	t_marco* marco = buscar_marco_libre_en_ram(proceso);

	if(hay_marco_libre(marco))
	{
		t_pagina* pagina = create_pagina(list_size(proceso->tabla_de_paginas), marco->num_marco, true, false);

		list_add(proceso->tabla_de_paginas, pagina);
	}

	if(no_hay_marco_libre(marco))
	{
		marco = swap_out(proceso);
	}

	return marco;
}

void asignarle_marcos(t_proceso* proceso, int cantidad_a_asignar)
{
	//pensar que no solo puede usar las paginas que estan reservadas si no trambien mas marcos que tieene en disco.
	if(string_equals_ignore_case(CONFIG_MEMORIA->TIPO_ASIGNACION, "FIJA"))
	{
		if(cant_marcos_libres() < cantidad_a_asignar)
		{
			error_mems(_start_process, "asignarle_marcos", "no hay tantos marcos libres para el proceso (asignacion fija)");
			//exit(1);
		}

	}

	for(int i=0; i<cantidad_a_asignar; i++)
	{
		asignar_marco(proceso);
	}

	printf("no quedan marcos libres en memoria para el %d ", proceso->pid);

}

void start_process(int pid)
{
	t_proceso* proceso = crear_proceso(pid);

	list_add(TABLA_GENERAL, proceso);

	if(string_equals_ignore_case(CONFIG_MEMORIA->TIPO_ASIGNACION, "FIJA"))
	{
		asignarle_marcos(proceso, CONFIG_MEMORIA->MARCOS_POR_CARPINCHO);
		asignar_primer_heapmetadata(proceso->tabla_de_paginas);
	}
}

void* siguiente_direccionn(t_list* paginas, int posicion)
{
	t_pagina* pagina = list_get(paginas, posicion);

	void* direccion_fisica = MI_MEMORIA + (pagina->marco_asignado * CONFIG_MEMORIA->TAMANIO_PAGINA + 0);

	return direccion_fisica;
}

void guardar_n_bytes(t_proceso* proceso, void* n_bytes, int num_pagina)
{
	t_marco* marco = buscar_marco_libre_en_mmu(proceso);

	if(marco==NULL)
		marco = swap_out(proceso);

	memcpy(marco->inicio, n_bytes, CONFIG_MEMORIA->TAMANIO_PAGINA);

	marco->pid = proceso->pid;
	marco->num_pagina = num_pagina;

}

t_pagina* swap_in(t_proceso* proceso, t_pagina* pagina)
{
	void* n_bytes = traer_n_bytes_de_disco(proceso->pid, pagina->num_pagina);

	guardar_n_bytes(proceso, n_bytes, pagina->num_pagina);

	pagina->esta_presente = true;
}

t_pagina* que_este_en_memoria(t_proceso* proceso, t_pagina* pagina)
{
	return pagina->esta_presente==true? pagina: swap_in(proceso, pagina);
}

t_heap_metadata* sacar_heap_metadata(t_proceso* proceso, int direccion_logica)
{
	int num_pagina = direccion_logica/CONFIG_MEMORIA->TAMANIO_PAGINA;
	int offset = direccion_logica % CONFIG_MEMORIA->TAMANIO_PAGINA;
	t_pagina* pagina = list_get(proceso->tabla_de_paginas, num_pagina);

	pagina = que_este_en_memoria(proceso, pagina);

	void* direccion_fisica = MI_MEMORIA + (pagina->marco_asignado * CONFIG_MEMORIA->TAMANIO_PAGINA + offset);

	t_heap_metadata* el_heap = NULL;
	int tam_del_heap = sizeof(el_heap);
	int espacio_disponible = CONFIG_MEMORIA->TAMANIO_PAGINA - offset;
	int aux = 0;

	while(tam_del_heap > espacio_disponible)
	{
		memcpy(el_heap + aux, direccion_fisica, espacio_disponible);
		aux = aux + espacio_disponible;
		direccion_fisica = siguiente_direccionn(proceso->tabla_de_paginas, num_pagina +1);
	}

	memcpy(el_heap, direccion_fisica, tam_del_heap);

	return el_heap;
}

t_pagina* primera_pagina(t_proceso* proceso)
{
	t_pagina* pagina = list_get(proceso->tabla_de_paginas, 0);

	return pagina;
}

int reserve_memory(int pid, int size)
{
	t_proceso* proceso = buscar_proceso(pid);

	if(proceso==NULL) error_mems(_reserve_memory, "reserve_memory", "proceso inexistente (nunca se inicio este proceso)");

	if(list_is_empty(proceso->tabla_de_paginas)) // si esta vacio es por que la asignacion es dinamica y no tiene marcos asignados.
	{
		asignar_marco(proceso);
		asignar_primer_heapmetadata(proceso);
	}

	void* direccion_fisica = buscar_espacio_entre_heaps();



}
/*
int memfree(alloc* porcion_memoria){
	porcion_memoria->heapMetadata->isFree = true;
	//Reviso si el siguiente alloc esta libre, si esta libre, lo consolido
	heapMetadata* nextHeapmetadata = obtener_heap_metadata(porcion_memoria->heapMetadata->nextAlloc);
	if(nextHeapmetadata->isFree){
		porcion_memoria->heapMetadata->nextAlloc = nextHeapmetadata->nextAlloc;
	}

	//Reviso si el anterior alloc esta libre, si esta libre, lo consolido
	heapMetadata* prevHeapmetadata = obtener_heap_metadata(porcion_memoria->heapMetadata->prevAlloc);
	if(nextHeapmetadata->isFree){
		porcion_memoria->heapMetadata->prevAlloc = prevHeapmetadata->prevAlloc;
	}
	return 0;
}



//Funcion para obtener el heapMetadata dada una pos de Alloc
heapMetadata* obtener_heap_metadata(uint32_t allocPos){
	heapMetadata* heapMetadata;
	memcpy(heapMetadata, mem+allocPos, sizeof(heapMetadata));
	return heapMetadata;
}

//Funcion para buscar nextAllocs libres, devuelve el nextAlloc del ultimo alloc libre (SOLO POR SI HAY QUE ITERAR)
uint32_t obtener_ultimo_nextAlloc_libre(heapMetadata *heapMetadata){
	while(heapMetadata->isFree){
		heapMetadata = obtener_heap_metadata(heapMetadata->nextAlloc);
	}
	return heapMetadata->nextAlloc;
}

//Funcion para buscar prevAllocs libres, devuelve el prevAlloc del ultimo alloc libre (SOLO POR SI HAY QUE ITERAR)
uint32_t obtener_ultimo_prevAlloc_libre(heapMetadata *heapMetadata){
	while(heapMetadata->isFree){
		heapMetadata = obtener_heap_metadata(heapMetadata->nextAlloc);
	}
	return heapMetadata->nextAlloc;
}



void* algoritmo_primer_ajuste(t_list* lista, int tamanio_a_guardar, int* pos, int* sobrante){
	PM* porcion1 = NULL;
	PM* porcion2 = NULL;
	void* direccion_de_memoria = NULL;
	int tamanio_disponible = 0;

	for(int i=0; i<list_size(lista)-1; i++)
	{
		porcion1 = list_get(lista, i);
		porcion2 = list_get(lista, i+1);
		tamanio_disponible = porcion2->inicio - porcion1->final;

		if(tamanio_disponible>=tamanio_a_guardar)
		{
			direccion_de_memoria = porcion1->final;
			*pos = i+1;
			break;
		}

	}

	return direccion_de_memoria;
}




 * */
