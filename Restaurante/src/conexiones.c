#include "conexiones.h"
#include "restaurante.h"
#include <socket.h>

void iniciar_servidor_restau(void)
{
	int socket_servidor;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo("127.0.0.1", PUERTO_ESCUCHA, &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p->ai_next)
    {
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_servidor);
            continue;
        }
        break;
    }

	listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);

    while(1)
    	esperar_cliente_restau(socket_servidor);
}

void esperar_cliente_restau(int socket_servidor)
{
	struct sockaddr_in dir_cliente;

	socklen_t tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

	pthread_t THREAD;
	pthread_create(&THREAD,NULL,(void*)serve_client_restau,&socket_cliente);
	pthread_detach(THREAD);

}

void serve_client_restau(int* socket)
{
	int el_socket = *socket;
	int cod_op;
	if(recv(el_socket, &cod_op, sizeof(int), MSG_WAITALL) == -1)
		cod_op = -1;
	process_request_restau(cod_op, el_socket);
}

void process_request_restau(int cod_op, int cliente_fd)
{
	void* stream = sacar_stream_de_buffer(cliente_fd);
	int socket_conexion;
	char* respuesta = NULL;
	t_pedido* pedido;
	int id_generado;
	char* nombre_plato = NULL;
	int id_pedido;
	switch (cod_op)
	{
		case consultar_platos:
			printf("\nah llegado a consultar platos\n");
			socket_conexion = crear_conexion_sindicato();
			consultar_platos_al_sindicato(socket_conexion, NOMBRE_RESTAURANTE);
			respuesta = recibimos_platos(socket_conexion);
			printf("los platos: %s", respuesta);
			enviar_respuesta(cliente_fd, respuesta);
			break;

		case crear_pedido:
			printf("\n crearPedido \n");
			socket_conexion = crear_conexion_sindicato();
			//id_generado = generar(ID_PEDIDO);
			//_guardar_pedido(socket_conexion, NOMBRE_RESTAURANTE, string_itoa(id_generado));
			respuesta = recibimos_confirmacion(socket_conexion);
			printf("confirmacion: %s", respuesta);
			enviar_respuesta_entero(cliente_fd, id_generado);
			break;

		case aniadir_plato:
			printf("\n aniadir_plato  \n");
			nombre_plato = sacar_cadena_de_stream(&stream);
			id_pedido = sacar_entero_de_stream(&stream);
			socket_conexion = crear_conexion_sindicato();
			//_guardar_plato(socket_conexion, NOMBRE_RESTAURANTE, string_itoa(id_pedido), nombre_plato, string_itoa(1)); // ver despues la cantidad por que se lo pusimos fijo
			respuesta = recibimos_confirmacion(socket_conexion); // oviamente la respuesta puede ser ok o fail
			printf("confirmacion: %s", respuesta);
			enviar_respuesta(cliente_fd, respuesta);
			break;

		case confirmar_pedido:
			printf("confirmar_pedido\n");
			id_pedido = sacar_entero_de_stream(&stream);
			socket_conexion = crear_conexion_sindicato();
			//_obtener_pedido(socket_conexion, NOMBRE_RESTAURANTE, string_itoa(id_pedido));
			pedido = recibimos_pedido(socket_conexion);
			//
			//
			generar_pcb_por_plato(pedido->platos);//completar_funcion y depsues mandarlo  a ciclo de planificacion -> usar _obtener_receta(socket_conexion, char* nombre_plato); el nombre del plato se saca de pedidos para se mas exacto listaplatos
			//
			enviar_respuesta(cliente_fd, "pedido_confirmado");
			break;

		case consultar_pedido:
			printf("\nconsultarPedido()\n");
			id_pedido = sacar_entero_de_stream(&stream);
			socket_conexion = crear_conexion_sindicato();
			//_obtener_pedido(socket_conexion, NOMBRE_RESTAURANTE, string_itoa(id_pedido));
			pedido = recibimos_pedido(socket_conexion);
			enviar_pedido(cliente_fd, pedido);
			break;

		case 0:
			pthread_exit(NULL);
		case -1:
			pthread_exit(NULL);
	}
}
void enviar_respuesta_entero(int cliente_fd, int id_generado)
{
	t_paquete* paquete = crear_paquete(confirmacion);
	agregar_entero_a_paquete(paquete, id_generado);
	enviar_paquete(paquete, cliente_fd);
}

void enviar_respuesta(int cliente_fd, char* palabra)
{
	t_paquete* paquete = crear_paquete(confirmacion);
	agregar_cadena_a_paquete(paquete, palabra, strlen(palabra) +1);
	enviar_paquete(paquete, cliente_fd);
}

void enviar_pedido(int cliente_fd, t_pedido* pedido)
{
	t_paquete* paquete = crear_paquete(confirmacion);
	agregar_cadena_a_paquete(paquete, pedido->estado_pedido, strlen(pedido->estado_pedido) +1);
	agregar_cadena_a_paquete(paquete, pedido->platos, strlen(pedido->platos) +1);
	agregar_cadena_a_paquete(paquete, pedido->cant_platos, strlen(pedido->cant_platos) +1);
	agregar_cadena_a_paquete(paquete, pedido->cant_lista, strlen(pedido->cant_lista) +1);
	agregar_entero_a_paquete(paquete, pedido->precio_total);

	enviar_paquete(paquete, cliente_fd);
}

void* serializar_paquete_restau(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}

void devolver_mensaje_restau(void* payload, int size, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = 1;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = size;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, payload, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete_restau(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

void consultar_platos_al_sindicato(int socket_conexion, char* nombre_restaurante)
{
	t_paquete* paquete = crear_paquete(consultar_platos);

	agregar_cadena_a_paquete(paquete, (void*)nombre_restaurante, strlen(nombre_restaurante) +1);

	enviar_paquete(paquete, socket_conexion);
}

char* recibimos_una_cadena(int socket_conexion)
{
	char* cadena = NULL;

	t_paquete* paquete = sacar_paquete(socket_conexion);

	if(paquete->codigo_operacion == confirmacion)
	{
		void* stream = paquete->buffer->stream;

		cadena = sacar_cadena_de_stream(&stream);

	}
	else
		printf("\nque cosa me enviaste sindicato??? \"%d\" \nyo solo queria una cadena \n", paquete->codigo_operacion);

	return cadena;
}

char* recibimos_platos(int socket_conexion)
{
	return recibimos_una_cadena(socket_conexion);
}

char* recibimos_confirmacion(int socket_conexion)
{
	return recibimos_una_cadena(socket_conexion);
}

t_pedido* recibimos_pedido(int socket_conexion)
{
	t_pedido* pedido = NULL;
	t_paquete* paquete = sacar_paquete(socket_conexion);
	if(paquete->codigo_operacion == confirmacion)
	{
		void* stream = paquete->buffer->stream;
		pedido = malloc(sizeof(t_pedido));
		pedido->estado_pedido = sacar_cadena_de_stream(&stream);
		pedido->platos = sacar_cadena_de_stream(&stream);
		pedido->cant_platos = sacar_cadena_de_stream(&stream);
		pedido->cant_lista = sacar_cadena_de_stream(&stream);
		pedido->precio_total = sacar_entero_de_stream(&stream);
	}
	else
		printf("\nque cosa me enviaste sindicato??? \"%d\" \nyo solo queria un pedido \n", paquete->codigo_operacion);

	return pedido;
}

void generar_pcb_por_plato(char* platos)
{
	//entra una lista de platos
	//generamos un pcb por cada plato


	//obtener receta a cada plato para sabher su movimiento en el momento de ejecucion
	// y dejarlo en el ciclo de planificaion
	//observacion se debe guardar en el pcb el numero de pedido
}







