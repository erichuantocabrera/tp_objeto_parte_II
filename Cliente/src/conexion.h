#ifndef CONEXION_H_
#define CONEXION_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <socket.h>

int crear_conexion_cliente(char *ip, char* puerto);
char* recibimos_el_mensaje(int socket_cliente);


#endif /* CONEXION_H_ */
