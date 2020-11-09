#include "Cliente.h"


int main(void)
{

	iniciar_datos_cliente();

	int conexion_cliente = iniciar_conexion();

	consola_cliente(conexion_cliente);

	sleep(2);//esperamos 2 segundos para ver si le envio el mensaje

	char* mensaje = recibimos_el_mensaje(conexion_cliente);

	if(mensaje != NULL)
		printf("\nme llego el mensaje: \"%s\"  \n", mensaje);

	else
		printf("\nWARNING no recibi mensaje\n");

	free(mensaje);
	close(conexion_cliente);
	return 0;

}


void iniciar_datos_cliente()
{
	MI_CONFIG = config_create("/home/utnso/tp-2020-2c-GrupoSOK3072/Cliente/src/Cliente.config");

	IP = config_get_string_value(MI_CONFIG, "IP");
	PUERTO = config_get_string_value(MI_CONFIG, "PUERTO");
	UBICACION_LOG = config_get_string_value(MI_CONFIG, "ARCHIVO_LOG");
	POSICION_X = config_get_int_value(MI_CONFIG, "POSICION_X");
	POSICION_Y = config_get_int_value(MI_CONFIG, "POSICION_Y");
	NOMBRE_CLIENTE = config_get_string_value(MI_CONFIG, "ID_CLIENTE");

	MI_LOG = log_create(UBICACION_LOG, "LugarDeLog", 1, LOG_LEVEL_INFO);
}


int iniciar_conexion()
{
	int conexion = crear_conexion_cliente(IP, PUERTO);

	if(conexion == -1)
	{
		printf("no se pudo realizar la conexion  \n");
		exit(1);
	}
	return conexion;
}


