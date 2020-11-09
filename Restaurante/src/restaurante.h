#ifndef RESTAURANTE_H_
#define RESTAURANTE_H_

#include <stdio.h>
#include <commons/log.h>
#include <commons/config.h>
#include <pthread.h>
#include "conexiones.h"
#include <socket.h>//para las conexion

typedef struct
{
	int cant_cocineros;			// 5
	char* posicion_mapa;		// "[4,5]"
	char* afinidad_cocineros;	// "[milanesa]"
	char* platos;				// "[milanesa,empanada,ensalada]"
	char* precios_platos;		// "[200,50,150]"
	int cant_hornos;			// 2
}t_restaurante;

typedef struct
{
	char* nombre;
	t_list* lista;
}t_afinidad;

typedef struct
{
	char* nombre;
	int cantidad;
	int id_pedido;
}t_pcb;


char* PUERTO_ESCUCHA;
char* IP_SINDICATO;
char* PUERTO_SINDICATO;
char* IP_APP;
char* PUERTO_APP;
int QUANTUM;
char* ARCHIVO_LOG;
char* ALGORITMO_PLANIFICACION;
char* NOMBRE_RESTAURANTE;

void iniciar_datos_restaurante();
void iniciar_hilo_escucha();
t_restaurante* obtencion_metadata_restaurante();
t_restaurante* recibimos_el_restaurante(int conexion);//despues scarla y dejarlo arriba asi no pongo esto
void crear_colas(t_restaurante* restaurante);

int crear_conexion_sindicato();
void crear_conexion_app();
int generar(int id);
t_restaurante* crear_restaurante_prueba();
void mostrar_lista_afinidades();


#endif /* RESTAURANTE_H_ */
