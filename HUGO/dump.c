/*
 * dump.c
 *
 *  Created on: 30 oct. 2021
 *      Author: utnso


#include "dump.h"


void crear_archivo_dump(char* path){
	FILE* dump = txt_open_for_append(path);
	char* metrica = string_new();
	char* fecha_actual = temporal_get_string_time();
	string_append(&metrica, "Dump: ");
	string_append(&metrica, fecha_actual);
	string_append(&metrica, "/n");
	txt_write_in_file(dump, metrica);
	txt_close_file(dump);
	free(metrica);
}

void nueva_entrada_dump(char* path, int numero_de_entrada,char* estado, int pid,int numero_de_pagina,int marco){
	char* entrada = string_new();
	string_append(&entrada, "Entrada: ");
	string_append(&entrada, numero_de_entrada);
	string_append(&entrada, "/n");
	string_append(&entrada, "Estado: ");
	string_append(&entrada, estado);
	string_append(&entrada, "/n");
	string_append(&entrada, "Carpincho: ");
	string_append(&entrada, pid);
	string_append(&entrada, "/n");
	string_append(&entrada, "Pagina: ");
	string_append(&entrada, numero_de_pagina);
	string_append(&entrada, "/n");
	string_append(&entrada, "Marco: ");
	string_append(&entrada, marco);
	string_append(&entrada, "/n");
	FILE* dump;
	dump = txt_open_for_append(path);
	txt_write_in_file(dump, entrada);
	txt_close_file(dump);
	free(entrada);
}

*/
