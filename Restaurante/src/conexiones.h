
#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <string.h>
#include <pthread.h>
#include "restaurante.h"

typedef struct
{
	char* estado_pedido;	// "confirmado"
	char* platos;			// "[milanesa,empanadas,ensalada]"
	char* cant_platos;		// "[2,12,1]"
	char* cant_lista;		// "[1,6,0]" <---- aun no se para que sirve esto
	int precio_total;		// 12390
} t_pedido;


void iniciar_servidor_restau(void);
void esperar_cliente_restau(int);
void serve_client_restau(int *socket);
void process_request_restau(int cod_op, int cliente_fd);
void devolver_mensaje_restau(void* payload, int size, int socket_cliente);
void enviar_confirmacion(int cliente_fd, char* palabra);

void consultar_platos_al_sindicato(int socket_conexion, char* NOMBRE_RESTAURANTE);
char* recibimos_platos(int socket_conexion);
char* recibimos_confirmacion(int socket_conexion);
void generar_pcb_por_plato(char* platos);
t_pedido* recibimos_pedido(int socket_conexion);
void enviar_respuesta(int cliente_fd, char* respuesta);
void enviar_respuesta_entero(int cliente_fd, int id_generado);

void enviar_pedido(int cliente_fd, t_pedido* pedido);

#endif /* CONEXIONES_H_ */
