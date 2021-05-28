#include "niv_gui.h"

static WINDOW * secwin;
static WINDOW * mainwin;
static int rows, cols;
static int inicializado = 0;

//============  FUNCIONES AUXILIARES  ===================================
int nivel_gui_get_term_size(int * filas, int * columnas, int infinit);            //|| Devuelve el tamanio total de la pantalla
char nivel_gui_item_show(ITEM_NIVEL* item);                          //|| Devuelve el caracter a mostrarse en pantalla
//=======================================================================

int nivel_gui_inicializar(int infinit)
{
//	if (nivel_gui_int_validar_inicializado())
//	{
//		return NGUI_ALREADY_INIT;
//	}

	mainwin = initscr();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
//	init_pair(1                  , COLOR_GREEN, COLOR_BLACK);//dibuja el contorno (marco).
	init_pair(PERSONAJE_ITEM_TYPE, COLOR_WHITE, COLOR_BLACK);
//	init_pair(CAJA_ITEM_TYPE     , COLOR_BLACK, COLOR_YELLOW);
//	init_pair(ENEMIGO_ITEM_TYPE  , COLOR_BLACK, COLOR_BLUE);
	box(stdscr, 0, 0);
	refresh();
	nivel_gui_get_term_size(&rows, &cols, infinit);
	secwin = newwin(rows - 3, cols, 0, 0);
	box(secwin, 0, 0);
	wrefresh(secwin);

	inicializado = 1;

	return NGUI_SUCCESS;

}

int nivel_gui_get_area_nivel(int * cols, int * rows, int infinit)
{

//	if (!nivel_gui_int_validar_inicializado()) {
//		return NGUI_NO_INIT;
//	}
//
	if(nivel_gui_get_term_size(rows, cols, infinit))
	{
		return NGUI_TERM_SIZE_FAIL;
	}

	if(rows) *rows = *rows - 5;
	if(cols) *cols = *cols - 2;

	return NGUI_SUCCESS;
}

int nivel_gui_dibujar(NIVEL* nivel)
{
//	if (!nivel_gui_int_validar_inicializado()) {
//		return NGUI_NO_INIT;
//	}

	char* srcs_text = string_duplicate("Recursos: ");

	werase(secwin);
	box(secwin, 0, 0);
	wbkgd(secwin, COLOR_PAIR(1));//------------------------------------- por que tenemos un color pair(1)

	void _draw_element(ITEM_NIVEL* item) {
		wmove(secwin, item->posy + 1, item->posx + 1);
		waddch(secwin, nivel_gui_item_show(item) | COLOR_PAIR(item->item_type));
		if (item->item_type == CAJA_ITEM_TYPE) {
			string_append_with_format(&srcs_text, "%c: %d - ", item->id, item->quantity);
		}
	}

	list_iterate(nivel->items, (void*) _draw_element);

	move(rows - 3, 2);
	printw("Nivel: %s - Tamanio: %dx%d", nivel->nombre, cols - 2, rows - 5);
	move(rows - 2, 2);
	printw(srcs_text);

	wrefresh(secwin);
	wrefresh(mainwin);

	free(srcs_text);

	return NGUI_SUCCESS;
}



/*---------------- Funciones utilitarias ----------------*/

int nivel_gui_get_term_size(int * rows, int * cols, int infinit) {

	printf("\nvalores entrantes rows: %d, cols: %d  infinit: %d  ", *rows, *cols, infinit);

	struct winsize ws;//<---------------------------------  estructura de ioctl

	if ( ioctl(0, TIOCGWINSZ, &ws) < 0 ) {
		infinit++;
		printf("\nvalores entrantes rows: %d, cols: %d  infinit: %d  ", *rows, *cols, infinit);
		return NGUI_TERM_SIZE_FAIL;
	}

	if(rows) *rows = ws.ws_row;
	if(cols) *cols = ws.ws_col;
	infinit++;
	printf("\nsale rows: %d, cols: %d infinit: %d  ", *rows, *cols, infinit);

	return NGUI_SUCCESS;
}


char nivel_gui_item_show(ITEM_NIVEL* item)
{
	return item->item_type == ENEMIGO_ITEM_TYPE ? '*' : item->id;
}
