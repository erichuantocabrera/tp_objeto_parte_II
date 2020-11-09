#include "mensajes.h"


void _consultar_restaurantes(int socket)
{
	t_paquete* paquete = crear_paquete(consultar_restaurantes);

	enviar_paquete(paquete, socket);
}

void _seleccionar_restaurante(int socket, char* cliente, char* nombre_restaurante)
{
	t_paquete* paquete = crear_paquete(seleccionar_restaurante);

	agregar_cadena_a_paquete(paquete, (void*)cliente, strlen(cliente) +1);
	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);

	enviar_paquete(paquete, socket);
}

void _obtener_restuarante(int socket, char* nombre_restaurante)
{
	t_paquete* paquete = crear_paquete(obtener_restaurante);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);

	enviar_paquete(paquete, socket);
}

void _consultar_platos(int socket, char* nombre_restaurante)
{
	t_paquete* paquete = crear_paquete(consultar_platos);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);

	enviar_paquete(paquete, socket);
}

void _aniadir_plato(int socket, char* nombre_plato, char* id_pedido)
{
	t_paquete* paquete = crear_paquete(aniadir_plato);

	agregar_cadena_a_paquete(paquete, (void*)nombre_plato, strlen(nombre_plato) +1);
	agregar_entero_a_paquete(paquete, atoi(id_pedido));

	enviar_paquete(paquete, socket);
}

void _guardar_plato(int socket, char* nombre_restaurante, char* id_pedido, char* comida, char* cantidad)
{
	t_paquete* paquete = crear_paquete(guardar_plato);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);
	agregar_entero_a_paquete(paquete, atoi(id_pedido));
	agregar_cadena_a_paquete(paquete, (void*)comida, strlen(comida) +1);
	agregar_entero_a_paquete(paquete, atoi(cantidad));

	enviar_paquete(paquete, socket);
}

void _plato_listo(int socket, char* nombre_restaurante, char* id_pedido, char* comida)
{
	t_paquete* paquete = crear_paquete(plato_listo);
	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);
	agregar_entero_a_paquete(paquete, atoi(id_pedido));
	agregar_cadena_a_paquete(paquete, (void*)comida, strlen(comida) +1);

	enviar_paquete(paquete, socket);
}

void _crear_pedido(int socket)
{
	t_paquete* paquete = crear_paquete(crear_pedido);//=================================================================================

	enviar_paquete(paquete, socket);
}

void _guardar_pedido(int socket, char* nombre_restaurante, char* id_pedido)
{
	t_paquete* paquete = crear_paquete(guardar_pedido);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);
	agregar_entero_a_paquete(paquete, atoi(id_pedido));

	enviar_paquete(paquete, socket);
}

void _consultar_pedido(int socket, char* id_pedido)
{
	t_paquete* paquete = crear_paquete(consultar_pedido);

	agregar_entero_a_paquete(paquete, atoi(id_pedido));

	enviar_paquete(paquete, socket);
}

void _obtener_pedido(int socket, char* nombre_restaurante, char* id_pedido)
{
	t_paquete* paquete = crear_paquete(obtener_pedido);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);
	agregar_entero_a_paquete(paquete, atoi(id_pedido));

	enviar_paquete(paquete, socket);
}

void _confirmar_pedido(int socket, char* id_pedido)
{
	t_paquete* paquete = crear_paquete(confirmar_pedido);

	agregar_entero_a_paquete(paquete, atoi(id_pedido));

	enviar_paquete(paquete, socket);
}

void _terminar_pedido(int socket, char* nombre_restaurante, char* id_pedido)
{
	t_paquete* paquete = crear_paquete(terminar_pedido);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);
	agregar_entero_a_paquete(paquete, atoi(id_pedido));

	enviar_paquete(paquete, socket);
}

void _finalizar_pedido(int socket, char* nombre_restaurante, char* id_pedido)
{
	t_paquete* paquete = crear_paquete(finalizar_pedido);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);
	agregar_entero_a_paquete(paquete, atoi(id_pedido));

	enviar_paquete(paquete, socket);
}

void _obtener_receta(int socket, char* nombre_plato)
{
	t_paquete* paquete = crear_paquete(obtener_receta);

	agregar_cadena_a_paquete(paquete, (void*)nombre_plato, strlen(nombre_plato) +1);

	enviar_paquete(paquete, socket);
}




