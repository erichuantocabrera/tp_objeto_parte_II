#include <conexiones.h>

int crearConexionCliente(String ip, int puerto, t_log* logger){
    struct addrinfo hints;
    struct addrinfo *servidorInfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, puerto, &hints, &servidorInfo);
    freeaddrinfo(hints);

    int socketCliente = socket(servidorInfo->ai_family,
                               servidorInfo->ai_socktype,
                               servidorInfo->ai_protocol);

    if(socketCliente == -1) {
        log_error(logger, "no se pudo crear el socket");
        exit(1);
    }

    socketCliente = connect(socketCliente,
                            servidorInfo->ai_addr,
                            servidorInfo->ai_addrlen);

    if(socketCliente == -1) {
        log_error(logger, "no se pudo conectar");
        exit(1);
    }

    freeaddrinfo(servidorInfo);
    return socketCliente;
}


void enviarMensaje(String stream, t_codigoDeOperacion codigoOp, int socket, t_log* logger) {
    t_buffer* buffer = malloc(sizeof(t_buffer));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    buffer->size = strlen(stream)+1;
    buffer->stream = malloc(buffer->size);
    memcpy(buffer->stream, stream, buffer->size);

    paquete->codigoDeOperacion = codigoOp;
    paquete->buffer = buffer;

    int bytes = sizeof(t_codigoDeOperacion)+buffer->size+sizeof(buffer->size);

    void* mensaje = serializar(paquete, bytes, logger);

    send(socket, mensaje, bytes, 0);
    log_info(logger, "se ha enviado el mensaje");

    free(buffer->stream);
    free(buffer);
    free(paquete);
    free(mensaje);
}

void* serializar(t_paquete* paquete, int bytes, t_log* logger) {
    void* mensaje = malloc(bytes);
    int aux = 0;

    memcpy(mensaje+aux, &(paquete->codigoDeOperacion), sizeof(t_codigoDeOperacion));
    aux += sizeof(t_codigoDeOperacion);

    memcpy(mensaje+aux, &(paquete->buffer->size), sizeof(int));
    aux += sizeof(int);

    memcpy(mensaje+aux,(paquete->buffer->stream), paquete->buffer->size);

    log_info(logger, "mensaje serializado");
    return mensaje;
}

String recibirMensaje(int socket, t_log* logger) {
    t_codigoDeOperacion codigoOp;
    int size;

    recv(socket, &codigoOp, sizeof(t_codigoDeOperacion), 0);
    recv(socket, &size, sizeof(int), 0);

    void* stream = malloc(size);
    recv(socket, stream, size, 0);

    t_buffer* buffer = malloc(sizeof(t_buffer));
    buffer->size = size;
    buffer->stream = stream;

    String mensaje = deserealizar(buffer);

    log_info(logger, "mensaje recibido");
    return mensaje;
}

String deserializar(t_buffer* buffer){
    return (String) (buffer->stream);
}

void cerrarConexion(int socket, t_log* logger) {
    close(socket);
    log_info(logger, "conexion cerrada");

}
