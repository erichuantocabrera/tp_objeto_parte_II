#ifndef MENSAJES_H_
#define MENSAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <socket.h>


void _consultar_restaurantes(int socket);
void _seleccionar_restaurante(int socket, char* cliente, char* nombre_restaurante);
void _obtener_restuarante(int socket, char* nombre_restaurante);
void _consultar_platos(int socket, char* nombre_restaurante); /*revisar con mas detalle este*/
void _aniadir_plato(int socket, char* nombre_plato, char* id_pedido);
void _guardar_plato(int socket, char* nombre_restaurante, char* id_pedido, char* comida, char* cantidad);
void _plato_listo(int socket, char* nombre_restaurante, char* id_pedido, char* comida);
void _crear_pedido(int socket);
void _guardar_pedido(int socket, char* nombre_restaurante, char* id_pedido);
void _consultar_pedido(int socket, char* id_pedido);
void _obtener_pedido(int socket, char* nombre_restaurante, char* id_pedido);
void _confirmar_pedido(int socket, char* id_pedido);
void _terminar_pedido(int socket, char* nombre_restaurante, char* id_pedido);
void _finalizar_pedido(int socket, char* nombre_restaurante, char* id_pedido);
void _obtener_receta(int socket, char* nombre_plato);


#endif /* MENSAJES_H_ */
