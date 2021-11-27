#include "funciones_extras.h"

void abortar_memoria(char* palabra)
{
	error_show(palabra);
	exit(1);
}

void inicializar_config()
{
	CONFIG_MEMORIA = malloc(sizeof(t_config_memoria)); //estructura config
	t_config* archivoConfig = config_create("../configMemoria.config");

	if(archivoConfig == NULL) abortar_memoria("error al crear config\n");

	CONFIG_MEMORIA->PUERTO_ESCUCHA = config_get_int_value(archivoConfig, "PUERTO");
	CONFIG_MEMORIA->TAMANIO = config_get_int_value(archivoConfig, "TAMANIO");
	CONFIG_MEMORIA->TAMANIO_PAGINA = config_get_int_value(archivoConfig, "TAMANIO_PAGINA");
	CONFIG_MEMORIA->ALGORITMO_REEMPLAZO_MMU  = config_get_string_value(archivoConfig, "ALGORITMO_REEMPLAZO_MMU");
	CONFIG_MEMORIA->TIPO_ASIGNACION  = config_get_string_value(archivoConfig, "TIPO_ASIGNACION");
	CONFIG_MEMORIA->MARCOS_POR_CARPINCHO = config_get_int_value(archivoConfig, "MARCOS_POR_CARPINCHO");
	CONFIG_MEMORIA->CANTIDAD_ENTRADAS_TLB = config_get_int_value(archivoConfig, "CANTIDAD_ENTRADAS_TLB");
	CONFIG_MEMORIA->ALGORITMO_REEMPLAZO_TLB = config_get_string_value(archivoConfig, "ALGORITMO_REEMPLAZO_TLB");
	CONFIG_MEMORIA->RETARDO_ACIERTO_TLB = config_get_int_value(archivoConfig, "RETARDO_ACIERTO_TLB");
	CONFIG_MEMORIA->RETARDO_FALLO_TLB = config_get_int_value(archivoConfig, "RETARDO_FALLO_TLB");
	CONFIG_MEMORIA->PATH_DUMP_TLB = config_get_string_value(archivoConfig, "PATH_DUMP_TLB");

	config_destroy(archivoConfig);

}

void reservamos_espacio_general()
{
	MI_MEMORIA = malloc(CONFIG_MEMORIA->TAMANIO);

	if(MI_MEMORIA == NULL) abortar_memoria("error al crear espacio de direcciones de memoria\n");
}

void dividimos_la_memoria_en_marcos() //nos servira mas adelante para enviar marcos al disco.
{
	TABLA_DE_MARCOS = list_create();

	int cant_marcos = CONFIG_MEMORIA->TAMANIO/CONFIG_MEMORIA->TAMANIO_PAGINA;

	for(int i=0; i<cant_marcos; i++)
	{
		t_marco* marco = malloc(sizeof(t_marco));

		marco->inicio = MI_MEMORIA + i*(CONFIG_MEMORIA->TAMANIO_PAGINA);
		marco->pid = -1;
		marco->num_marco = i;
		marco->esta_libre = true;
		//marco->final = la_memoria + (i+1)*(CONFIG_MEMORIA->TAMANIO_PAGINA);

		list_add(TABLA_DE_MARCOS, marco);
	}
}

void creamos_tabla_general()
{
	TABLA_GENERAL = list_create();
}

void inicializar_memoria()
{
	reservamos_espacio_general();

	dividimos_la_memoria_en_marcos();

	creamos_tabla_general();
}

void inicializar_logs()
{
	LOGGER = log_create("../tp.log","MEMORIA",1,LOG_LEVEL_INFO );

	if(LOGGER == NULL) abortar_memoria("error al crear el log\n");
}

void iniciar_memoria()
{
	inicializar_config();
	inicializar_memoria();
	inicializar_logs();

}


