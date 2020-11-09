#ifndef CONSOLA_H_
#define CONSOLA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <commons/string.h>
#include <readline/readline.h> // Libreria que nos facilita la lectura de cadenas. Recordar liberar la memoria que asiga
#include <readline/history.h> // Libreria que nos permite incorporar la funcionalidad de historial para nuestra consola

#include "Cliente.h"

typedef struct {
	char* name; // Nombre del comando
	Function* f; // Funcion asociada al comando
	int parametros; // Cantidad de parametros
}CMD;


void consola_cliente(int conexion);
void mostrar_opciones();
void agregar_funcion_tab();
void agregar_al_historial(char* input);
void ejecutar_linea(int conexion, char* input);


#endif /* CONSOLA_H_ */
