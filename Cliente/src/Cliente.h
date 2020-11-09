#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdio.h>
#include <commons/log.h>
#include <commons/config.h>
#include <unistd.h>//ṕor el sleep();

#include "conexion.h"//por crear_conexion_cliente();
#include "mensajes.h"//por crear_pedido();
#include "consola.h"




t_config* MI_CONFIG;
t_log* MI_LOG;

char* IP;
char* PUERTO;
char* UBICACION_LOG;
int POSICION_X;
int POSICION_Y;
char* NOMBRE_CLIENTE;

void iniciar_datos_cliente();
int iniciar_conexion();
void consolaInteractiva();

void levantar_consola();
void iniciar_conexion_con_alguien();
void leer_respuesta(int socket);


#endif /* CLIENTE_H_ */


