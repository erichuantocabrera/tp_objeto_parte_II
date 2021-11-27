/*
 * dump.h
 *
 *  Created on: 30 oct. 2021
 *      Author: utnso


#ifndef DUMP_H_
#define DUMP_H_

#include <commons/temporal.h>
#include <string.h>
#include <stdlib.h>

void crear_archivo_dump(char* path);
void nueva_entrada_dump(char* path, int numero_de_entrada,char* estado, int pid,int numero_de_pagina,int marco);

#endif /* DUMP_H_ */
