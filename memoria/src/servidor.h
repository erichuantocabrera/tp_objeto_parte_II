#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#define _iniciar_patota_                    1
#define _iniciar_tripulante_                2
#define _recibir_ubicacion_del_tripulante_  3
#define _enviar_proxima_tarea_              4
#define expulsar_tripulante                 5

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <commons/string.h>
#include <string.h>


void iniciar_servidor(void);


#endif /* SERVIDOR_H_ */
