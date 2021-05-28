#include "funciones.h"
#include "servidor.h"

t_config* MI_CONFIG;
void* memoria_Ram;
int TAMANIO_MEMORIA;
char* ESQUEMA_MEMORIA;
int TAMANIO_PAGINA;
int TAMANIO_SWAP;
char* PATH_SWAP;
char* ALGORITMO_REMPLAZO;
int PUERTO;

//=============== FUNCIONES AUXILIARES==================
void reservar_espacio();
void dibujar_mapa();
void inicializar_servidor();
//======================================================

void iniciar_variables()
{
	MI_CONFIG = config_create("/home/utnso/workspace/memoria/src/memoria.config");

	TAMANIO_MEMORIA = config_get_int_value(MI_CONFIG, "TAMANIO_MEMORIA");
	ESQUEMA_MEMORIA = config_get_string_value(MI_CONFIG, "ESQUEMA_MEMORIA");
	TAMANIO_PAGINA = config_get_int_value(MI_CONFIG, "TAMANIO_PAGINA");
	TAMANIO_SWAP = config_get_int_value(MI_CONFIG, "TAMANIO_SWAP");
	PATH_SWAP = config_get_string_value(MI_CONFIG, "PATH_SWAP");
	ALGORITMO_REMPLAZO = config_get_string_value(MI_CONFIG, "ALGORITMO_REMPLAZO");
	PUERTO = config_get_int_value(MI_CONFIG, "PUERTO");
}

void inicializar_memoria()
{
	reservar_espacio();
	dibujar_mapa();
	inicializar_servidor();
}

void reservar_espacio()
{
	//printf("memoria esta: %p", memoria_Ram);
	memoria_Ram = malloc(TAMANIO_MEMORIA);
	//printf("memoria esta: %p", memoria_Ram);

}
void dibujar_mapa()
{
	//usar funciones que todavia no conosco
}
void inicializar_servidor()
{

	pthread_t hilo;

	pthread_create(&hilo, NULL, (void*)iniciar_servidor, NULL);

	//pthread_join(hilo, NULL);
	pthread_detach(hilo); // rebisar esta parte para saber si join o detach
}

void finalizar_variables()
{
	config_destroy(MI_CONFIG);
}



