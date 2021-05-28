#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "niv_gui.h"
#include "tad_niv.h"

int infinit = 0;
int main(void)
{
	NIVEL* nivel;

	int cols, rows, err=-1;

	nivel_gui_inicializar(infinit);

	nivel_gui_get_area_nivel(&cols, &rows, infinit);
//	printf("\n     cols: %d, rows: %d, err: %d,  \n\n", cols, rows, err);//ya tenemos los tamaños de la pantalla
/*
	nivel = nivel_crear("en casa compilaba");

	err = personaje_crear(nivel, 'A', cols - 1, rows - 1);

	err = personaje_crear(nivel, 'B', 0, 0);

//	err = enemigo_crear(nivel, '1', 10, 14);
//	err = enemigo_crear(nivel, '2', 20, 3);


	while ( 1 ) {
		nivel_gui_dibujar(nivel);

		int key = getch();

		switch( key )
		{
			case KEY_UP:
				err = item_desplazar(nivel, 'A', 0, -1);
			break;

			case KEY_DOWN:
				err = item_desplazar(nivel, 'A', 0, 1);
			break;

			case KEY_LEFT:
				err = item_desplazar(nivel, 'A', -1, 0);
			break;
			case KEY_RIGHT:
				err = item_desplazar(nivel, 'A', 1, 0);
			break;

			case 'w':
			case 'W':
				err = item_desplazar(nivel, 'B', 0, -1);
			break;

			case 's':
			case 'S':
				err = item_desplazar(nivel, 'B', 0, 1);
			break;

			case 'a':
			case 'A':
				err = item_desplazar(nivel, 'B', -1, 0);
			break;

			case 'D':
			case 'd':
				err = item_desplazar(nivel, 'B', 1, 0);
			break;

			case 'Q':
			case 'q':
//				nivel_destruir(nivel);
//				nivel_gui_terminar();
			//	return EXIT_SUCCESS;
			break;
		}

		if(err)
		{
//			printf("WARN: %s\n", nivel_gui_string_error(err));
			printf("adios perros");
		}

//		item_desplazar(nivel, '1', rnd(), rnd());
//		item_desplazar(nivel, '2', rnd(), rnd());

	}
*/
	infinit = -5;
}
