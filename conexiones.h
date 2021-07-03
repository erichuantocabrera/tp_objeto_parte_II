#ifndef CONEXIONES_H_
#define CONEXIONES_H_

	#include <stdbool.h>
	#include <stdlib.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <string.h>
    #include <stdio.h>
    #include <readline/readline.h>
    #include <commons/log.h>
    #include <commons/string.h>
    #include <commons/config.h>


//Typedefs enum
	typedef enum {
		INICIAR_PATOTA,
		LISTAR_TRIPULANTES,
		EXPULSAR_TRIPULANTE,
		OBTENER_BITACORA,         //TODO
	}t_codigoDeOperacion;



//Typedefs Structs
	typedef struct {
		int size;			//tamaño del payload
		void* stream;		//payload
	}t_buffer;



	typedef struct{
	    t_codigoDeOperacion codigoDeOperacion;		//header
	    t_buffer* buffer;							//payload y su tamaño
	} t_paquete;



//definiciones
	typedef char* String;



//prototipos
	int crearConexionCliente(String ip, int puerto, t_log* logger);
	void enviarMensaje(String stream, t_codigoDeOperacion codigoOp, int socket);
	void* serializar(t_paquete* paquete, int bytes);
	String recibirMensaje(int socket);
	String deserializar(t_buffer* buffer);
	void cerrarConexion(int socket);


#endif
