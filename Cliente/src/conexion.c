#include "conexion.h"


int crear_conexion_cliente(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if( connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		return -1; //		printf("error al crear_conexion");

	freeaddrinfo(server_info);

	return socket_cliente;
}


char* recibimos_el_mensaje(int socket_cliente)
{
	char* mensaje = NULL;
	t_paquete* paquete = sacar_paquete(socket_cliente);

	if(paquete->codigo_operacion == respuesta)
		mensaje = sacar_cadena_de_stream(&(paquete->buffer->stream));

	else
		printf("\nque cosa me enviaste como confirmacion??? \"%d\"  \n", paquete->codigo_operacion);

	return mensaje;
}
