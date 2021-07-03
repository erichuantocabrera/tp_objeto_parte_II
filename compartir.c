
t_buffer* crear_buffer()
{
	t_buffer* buffer = malloc(sizeof(t_buffer));

    buffer->size = 0;
    buffer->stream = NULL;

    return buffer;
}

t_paquete* crear_paquete(t_codigoDeOperacion cod_op)
{
    t_paquete* paquete = malloc(sizeof(t_paquete));

    paquete->codigoDeOperacion = cod_op;
    paquete->buffer = crear_buffer();

    return paquete;
}

void agregar_cadena_a_paquete(t_paquete* paquete, char* cadena, int tamanio_de_la_cadena)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + sizeof(int) + tamanio_de_la_cadena );

	memcpy(paquete->buffer->stream + paquete->buffer->size, &tamanio_de_la_cadena, sizeof(int));
	memcpy(paquete->buffer->stream + paquete->buffer->size + sizeof(int), cadena, tamanio_de_la_cadena);

	paquete->buffer->size += sizeof(int) + tamanio_de_la_cadena ;
}

void agregar_entero_a_paquete(t_paquete* paquete, int numero, int tamanio)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + sizeof(int));

	memcpy(paquete->buffer->stream + paquete->buffer->size, &numero, tamanio); // tamanio o sizeof(int), debido a que tamanio es 4

	paquete->buffer->size += tamanio ;
}

void agregar_caracter_a_paquete(t_paquete* paquete, char caracter, int tamanio)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + sizeof(char));

	memcpy(paquete->buffer->stream + paquete->buffer->size, &caracter, tamanio); // verificar si el memcpy funciona para caracteres

	paquete->buffer->size += tamanio ;
}

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}
