#ifndef TAD_NIV_H_
#define TAD_NIV_H_

#include "niv_gui.h"
#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <commons/collections/list.h>
#include <commons/string.h>


//	* @DESC: Crea el mapa con un nombre e inicializa la lista de objetos del mapa.
NIVEL* nivel_crear(char* nombre);

// @DESC: Crea una instancia de personaje que se mostrará
// en el nivel con el caracter que lo identifica en color
// blanco y fondo en negro.
int personaje_crear(NIVEL* nivel, char id, int x , int y);

// @DESC: Desplaza el item tomando a su posición actual
// como pivote. En caso de desplazarse fuera de la pantalla,
// no realiza ninguna acción.
int item_desplazar(NIVEL* nivel, char id, int offset_x, int offset_y);


#endif /* TAD_NIV_H_ */
