/*
 * logs.c
 *
 *  Created on: 29 oct. 2021
 *      Author: utnso



#include <logs.h>

void log_TLB_Hit(int Pid,int numero_pagina,int marco){
	char* mensaje = string_new();
	string_append(&mensaje, "TLB_Hit PID= ");
	string_append(&mensaje, Pid);
	string_append(&mensaje, " Numero de Pagina= ");
	string_append(&mensaje, numero_pagina);
	string_append(&mensaje, " Marco= ");
	string_append(&mensaje, marco);
	log_info(logger,mensaje);
	free(mensaje);
}


void log_TLB_Miss(int Pid,int numero_pagina){
	char* mensaje = string_new();
	string_append(&mensaje, "TLB_Miss PID= ");
	string_append(&mensaje, Pid);
	string_append(&mensaje, " Numero de Pagina= ");
	string_append(&mensaje, numero_pagina);
	log_info(logger,mensaje);
	free(mensaje);
}


void log_conexion(int id){
	char* mensaje = string_from_format("Se conectó correctamente el carpincho de id %d",id);

	log_info(logger,mensaje);
	free(mensaje);
}

void log_desconexion(int id){
	char* mensaje = string_from_format("Se ha desconectado el carpincho de id %d",id);

	log_info(logger,mensaje);
	free(mensaje);
}


void logs_reemplazo_entrada(int Pid, int numero_pagina, int marco, int Pid2, int numero_pagina2){
	char* mensaje = string_new();
	string_append(&mensaje, "Reemplazo Victima PID= ");
	string_append(&mensaje, Pid);
	string_append(&mensaje, " Numero de Pagina= ");
	string_append(&mensaje, numero_pagina);
	string_append(&mensaje, " Marco= ");
	string_append(&mensaje, marco);
	string_append(&mensaje, "Reemplazo Victima PID= ");
	string_append(&mensaje, Pid2);
	string_append(&mensaje, " Numero de Pagina= ");
	string_append(&mensaje, numero_pagina2);
	string_append(&mensaje, " Marco= ");
	string_append(&mensaje, marco2);
	log_info(logger,mensaje);
	free(mensaje);
}


*/



