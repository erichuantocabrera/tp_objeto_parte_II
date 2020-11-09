#include "restaurante.h"

t_list* NEW;
t_list* READY;
t_list* EXECUT;
t_list* BLOCK;
t_list* EXIT;


int ID_PEDIDO;


int main(void)
{

//	iniciar_datos_restaurante();

//	t_restaurante* restaurante = obtencion_metadata_restaurante();
	t_restaurante* restaurante = crear_restaurante_prueba();
	crear_colas(restaurante);

//	mostrar_lista_afinidades();

	/*se empiezan a comunicar entre eprocessos  y genero los pcb de los platos*/
	crear_pcb_y_enviar_new(pedido1);
	crear_pcb_y_envair_new(pedido2);

//	iniciar_hilo_escucha();//en un hilo para clientes

	printf("\nadios");

	return EXIT_SUCCESS;
}





void iniciar_datos_restaurante()
{
	t_config* MI_CONFIG;
	t_log* mi_log;

	MI_CONFIG = config_create("/home/utnso/tp-2020-2c-GrupoSOK3072/Restaurante/src/Restaurante.config");

	PUERTO_ESCUCHA = config_get_string_value(MI_CONFIG, "PUERTO_ESCUCHA");
	IP_SINDICATO = config_get_string_value(MI_CONFIG, "IP_SINDICATO");
	PUERTO_SINDICATO = config_get_string_value(MI_CONFIG, "PUERTO_SINDICATO");
	IP_APP = config_get_string_value(MI_CONFIG, "IP_APP");
	PUERTO_APP = config_get_string_value(MI_CONFIG, "PUERTO_APP");
	QUANTUM = config_get_int_value(MI_CONFIG, "QUANTUM");
	ARCHIVO_LOG = config_get_string_value(MI_CONFIG, "ARCHIVO_LOG");
	ALGORITMO_PLANIFICACION = config_get_string_value(MI_CONFIG, "ALGORITMO_PLANIFICACION");
	NOMBRE_RESTAURANTE = config_get_string_value(MI_CONFIG, "NOMBRE_RESTAURANTE");

	mi_log = log_create(ARCHIVO_LOG, "LugarDeLog", 1, LOG_LEVEL_INFO);

	//ID_PEDIDO = 0;
}

void iniciar_hilo_escucha()
{
	pthread_t hilo;

	pthread_create(&hilo, NULL, (void*)iniciar_servidor_restau, NULL);

	//pthread_join(hilo, NULL);
	pthread_detach(hilo); // rebisar esta parte para saber si join o detach cual va.....
}


int crear_conexion_sindicato()
{
	int conexion = crear_conexion(IP_SINDICATO, PUERTO_SINDICATO);
	if(conexion == -1)
	{
		printf("error al crear_conexion_sindicato");
		exit(1);
		return -1;
	}
	else
		return conexion;
}
/*
void crear_conexion_app()
{
	CONEXION_APP = crear_conexion(IP_APP, PUERTO_APP);
	if(CONEXION_APP == -1)
	{
		printf("error al crear_conexion_sindicato");
		exit(1);
	}
}

*/
/*
void enviar_mensaje_onbtener_restaurante(int conexion_sindicato, char* NOMBRE_RESTAURANTE)
{
	t_paquete* paquete = crear_paquete(obtener_restaurante);

	agregar_cadena_a_paquete(paquete, (void*)NOMBRE_RESTAURANTE, strlen(NOMBRE_RESTAURANTE) +1);

	enviar_paquete(paquete, conexion_sindicato);
}
*/
t_restaurante* obtencion_metadata_restaurante()
{
	 int conexion_sindicato = crear_conexion_sindicato();
	 //_obtener_restuarante(conexion_sindicato, NOMBRE_RESTAURANTE);
	 t_restaurante* restaurante = recibimos_el_restaurante(conexion_sindicato); // verificar que hacer si me devuelve NULL

	 if(restaurante == NULL)
	 {
		 printf("sindicato no me enviaste ningun dato de mi. en obtencion metadata restaurante falle");
		 exit(-1);
	 }

	 return restaurante;
}

t_restaurante* recibimos_el_restaurante(int conexion)
{
	t_restaurante* restaurante = NULL;
	t_paquete* paquete = sacar_paquete(conexion);

	if(paquete->codigo_operacion == respuesta)
	{
		void* stream = paquete->buffer->stream;
		restaurante = malloc(sizeof(t_restaurante));

		restaurante->cant_cocineros = sacar_entero_de_stream(&stream);
		restaurante->posicion_mapa = sacar_cadena_de_stream(&stream);
		restaurante->afinidad_cocineros = sacar_cadena_de_stream(&stream);
		restaurante->platos = sacar_cadena_de_stream(&stream);
		restaurante->precios_platos = sacar_cadena_de_stream(&stream);
		restaurante->cant_hornos = sacar_entero_de_stream(&stream);
		//ver si hay unaa cantidad_pedidos y ver para que se lo envio.
	}
	else
		printf("\nque cosa me enviaste sindicato??? \"%d\" \nyo solo queria datos de mi restaurante \n", paquete->codigo_operacion);

	return restaurante;
}

int cantidad_de_palabras(char** doble_char)
{
	int i = 0;
	while(*doble_char != NULL) //mientras no encuentre null sigue
	{
		i++;
		doble_char++;
	}
	return i;
}

void mostrar_afinidades(char** afinidades)
{
	while(*afinidades != NULL) //mientras no encuentre null sigue
	{
		printf(" \"%s\" ", *afinidades);
		afinidades++;
	}
	printf("\n");
}


void crear_colas(t_restaurante* restaurante)
{
	NEW = list_create();
	READY = list_create();
	EXECUT = list_create();
	BLOCK = list_create();
	EXIT = list_create();

	char** afinidades = string_get_string_as_array(restaurante->afinidad_cocineros);

	int cant_afinidades = cantidad_de_palabras(afinidades);

	//creamos las n colas ready
	for(int i=0; i<cant_afinidades; i++)
	{
		t_afinidad* afinidad = malloc(sizeof(t_afinidad));
		afinidad->nombre = string_duplicate(afinidades[i]);
		afinidad->lista = list_create();
		printf("%s ", afinidades[i]);
		list_add(READY, afinidad);
	}

	//creamos las n colas de bloqueo
	for(int i=0; i<restaurante->cant_hornos; i++)
	{
		t_list* lista = list_create();
		list_add(BLOCK, lista);
	}

	//liberamos afinidades
	for(int i=0; i<cant_afinidades; i++)
		free(afinidades[i]);
	free(afinidades);
}


t_restaurante* crear_restaurante_prueba()
{
	t_restaurante* restaurante = malloc(sizeof(t_restaurante));

	restaurante->cant_cocineros = 5;
	restaurante->posicion_mapa = string_duplicate("[4,5]");
	restaurante->afinidad_cocineros = string_duplicate("[destrozar,revanar,triturar]");
	restaurante->platos = string_duplicate("[milanesas,empanadas,ensaladas]");
	restaurante->precios_platos = string_duplicate("[200,50,150]");
	restaurante->cant_hornos = 2;

	return restaurante;
}

int generar(int id)
{
	id++;
	return id;
}


void mostrar_lista_afinidades()
{
	for(int i=0; i<list_size(READY); i++)
	{
		char* nombre = ((t_afinidad*)list_get(READY, i))->nombre;
		printf("\"%s+%p\" ", nombre, nombre);
	}
	printf("\n");
}




