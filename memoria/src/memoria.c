#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

t_config* MI_CONFIG;
void* memoria_Ram;
int TAMANIO_MEMORIA;
char* ESQUEMA_MEMORIA;
int TAMANIO_PAGINA;
int TAMANIO_SWAP;
char* PATH_SWAP;
char* ALGORITMO_REMPLAZO;
int PUERTO;

int main(void)
{

	iniciar_variables();


	inicializar_memoria();


	finalizar_variables();

	return EXIT_SUCCESS;
}




