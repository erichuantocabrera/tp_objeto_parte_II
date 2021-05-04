#include "tad_niv.h"

//=========  FUNCIONES AUXILIARES  =============================================
int _crear_item(NIVEL* nivel, char id, int x, int y, int tipo, int cant);    //||
ITEM_NIVEL* _search_item_by_id(NIVEL* nivel, char id);                    	 //||
int _cambiar_posicion(ITEM_NIVEL* item, int x, int y);						 //||

//==============================================================================


NIVEL* nivel_crear(char* nombre)
{
	NIVEL* nivel = malloc(sizeof(NIVEL));

	nivel->nombre = string_duplicate(nombre);
	nivel->items = list_create();

	return nivel;
}

int personaje_crear(NIVEL* nivel, char id, int x , int y) {
	return _crear_item(nivel, id, x, y, PERSONAJE_ITEM_TYPE, 0);
}

int item_desplazar(NIVEL* nivel, char id, int offset_x, int offset_y) {
	ITEM_NIVEL* item = _search_item_by_id(nivel, id);

//	if (item == NULL)
//	{
//		return NGUI_ITEM_NOT_FOUND;
//	}

	return _cambiar_posicion(item, item->posx + offset_x, item->posy + offset_y);
}




//=========  FUNCIONES AUXILIARES  =============================================
int _crear_item(NIVEL* nivel, char id, int x , int y, int tipo, int cant_rec) {
//	if(!_validar_posicion(x, y)) {
//		return NGUI_ITEM_INVALID_POSITION;
//	}

//	if (_search_item_by_id(nivel, id) != NULL) {
//		return NGUI_ITEM_ALREADY_EXISTS;
//	}

	ITEM_NIVEL* item = malloc(sizeof(ITEM_NIVEL));

	item->id = id;
	item->posx=x;
	item->posy=y;
	item->item_type = tipo;
	item->quantity = cant_rec;

	list_add(nivel->items, item);

	return NGUI_SUCCESS;
}

ITEM_NIVEL* _search_item_by_id(NIVEL* nivel, char id) {
	bool _search_by_id(ITEM_NIVEL* item) {
		return item->id == id;
	}

	return list_find(nivel->items, (void*) _search_by_id);
}

int _cambiar_posicion(ITEM_NIVEL* item, int x, int y)
{
//	if (!_validar_posicion(x, y))
//	{	return NGUI_ITEM_INVALID_POSITION;
//	}

	item->posx = x;
	item->posy = y;

	return NGUI_SUCCESS;
}
