/*
 * logs.h
 *
 *  Created on: 29 oct. 2021
 *      Author: utnso


#ifndef LOGS_H_
#define LOGS_H_

#include <commons/log.h>
#include <commons/string.h>

void iniciar_logger();
void log_TLB_Hit(int Pid,int numero_pagina,int marco);
void log_TLB_Miss(int Pid,int numero_pagina);
void log_conexion(int id);
void log_desconexion(int id);
void logs_reemplazo_entrada(int Pid, int numero_pagina, int marco, int Pid2, int numero_pagina2);


t_log* logger;

#endif LOGS_H_ */
