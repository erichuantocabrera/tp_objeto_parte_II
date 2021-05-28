#ifndef NIV_GUI_H_
#define NIV_GUI_H_

#define PERSONAJE_ITEM_TYPE 2
#define CAJA_ITEM_TYPE      3
#define ENEMIGO_ITEM_TYPE   4
#define NGUI_SUCCESS                0//Operacion exitosa.
#define NGUI_TERM_SIZE_FAIL        -9//Error al obtener el tamaño de la terminal


#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <commons/string.h>
#include <commons/collections/list.h>


typedef struct nivel
{
	char* nombre;
	t_list* items;
} NIVEL;

typedef struct item {
	char id;
	int posx;
	int posy;
	int item_type; // PERSONAJE, ENEMIGO o CAJA
	int quantity;
} ITEM_NIVEL;

// @DESC: Inicializa el espacio de dibujo
int nivel_gui_inicializar(int infinit);
// @DESC: Devuelve el tamanio usable de la pantalla
int nivel_gui_get_area_nivel(int * columnas, int * filas, int infinit);
// @DESC: Dibuja cada entidad en la lista de items
int nivel_gui_dibujar(NIVEL* nivel);






#endif /* NIV_GUI_H_ */
