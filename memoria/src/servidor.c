#include "servidor.h"
int PUERTO;

//=====================FUNCIONES AUXILIARES========================
void recibi_algo_completo(int* socket);
void procesar_lo_recibido(int cod_op, int cliente_fd);
//=================================================================

void iniciar_servidor(void)
{
	int socket_servidor;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo("127.0.0.1", string_itoa(PUERTO), &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p->ai_next)
    {
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_servidor);//--->unistd.h unica funcion quue usa esa libreria
            continue;
        }
        break;
    }

	listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);

    while(1)
    {
    	struct sockaddr_in dir_cliente;

    	socklen_t tam_direccion = sizeof(struct sockaddr_in);

    	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

    	pthread_t THREAD;
    	pthread_create(&THREAD,NULL,(void*)recibi_algo_completo,&socket_cliente);
    	pthread_detach(THREAD);

    }
}

void recibi_algo_completo(int* socket)
{
	int el_socket = *socket;
	int cod_op;
	if(recv(el_socket, &cod_op, sizeof(int), MSG_WAITALL) == -1)
		cod_op = -1;
	procesar_lo_recibido(cod_op, el_socket);
}

void procesar_lo_recibido(int cod_op, int cliente_fd)
{
	//void* stream = sacar_stream_de_buffer(cliente_fd);
	switch (cod_op)
	{
		case _iniciar_patota_:


			break;

		case _iniciar_tripulante_:

			break;

		case _recibir_ubicacion_del_tripulante_:

			break;

		case _enviar_proxima_tarea_:

			break;

		case expulsar_tripulante:

			break;

		case 0:
			pthread_exit(NULL);
		case -1:
			pthread_exit(NULL);
	}
}
