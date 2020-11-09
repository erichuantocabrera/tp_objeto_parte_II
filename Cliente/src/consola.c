#include "consola.h"

CMD _cmd[]={
		{"consultar_restaurante", _consultar_restaurantes, 0},
		{"seleccionar_restaurante", _seleccionar_restaurante, 2},
		{"obtener_restauante", _obtener_restuarante, 1},
		{"consultar_platos", _consultar_platos, 1},
		{"aniadir_plato", _aniadir_plato, 2},
		{"guardar_plato", _guardar_plato, 4},
		{"plato_listo", _plato_listo, 3},
		{"crear_pedido", _crear_pedido, 0},
		{"guardar_pedido", _guardar_pedido, 2},
		{"consultar_pedido", _consultar_pedido, 1},
		{"obtener_pedido", _obtener_pedido, 2},
		{"confirmar_pedido", _confirmar_pedido, 1},
		{"terminar_pedido", _terminar_pedido, 2},
		{"finalizar_pedido", _finalizar_pedido, 2},
		{"obtener_receta", _obtener_receta, 1},
};


void consola_cliente(int conexion)
{
	char* input = NULL;

	printf("\nLinea de comandos\n");
	mostrar_opciones();
									   //Lo siguiente es para autoscompletar los comandos
	agregar_funcion_tab();    	   	   //Creamos completa_comandos para que ademas de poder autocompletar los
   	   	   	   	   	   	   	   	   	   //ficheros en directorio actual tambien podamos autocompletar los comandos
   	   	   	   	   	   	   	   	   	   //que nosotros añadamos

//	while(1)
//	{
		input = readline("> ");

//	    if(string_is_empty(input))//      <-------- if de corte si el string es vacio
//	    {
//	    	printf("\nchau chau adios \n");
//	    	break;
//	    }

	    string_trim(&input); // quita espacios innecesarios que se agregan cuando se usa tab.
	    printf ("Tu comando fue: \"%s\"  \n", input);

		agregar_al_historial(input); // Agregamos nuestro comando al historial.. para que se pueda usar con las flechas de arriba y abajo

		ejecutar_linea(conexion, input);

		free(input);
		printf("\n");
//	}
}

//==================   AGREGAR AL HISTORIAL  ==============================
void agregar_al_historial(char* input)
{
	add_history (input);
}
//=========================================================================
void dibujar_parametros(int cant_parametros)
{
	for(int i=0; i<cant_parametros; i++)
	{
		printf(" - ");
	}
	printf("\n");
}

void mostrar_opciones()
{
	for(int i=0; _cmd[i].name; i++)
	{
		printf("%30s ", _cmd[i].name);
		dibujar_parametros(_cmd[i].parametros);
	}
}

//=========================================================================

//==================   EJECUTAR LINEA  ====================================


bool verificar_cant_de_parametros(CMD* comando, int parametro)
{
	if(comando->parametros == parametro)
		return true;
	else
		return false;
}

int cantidad_de_palabras(char** doble_char)
{
	int i = 0;
	while(*doble_char!=NULL) //mientras no encuentre null sigue
	{

		printf(" \"%s\" ", *doble_char);
		i++;
		doble_char++;
	}
	return i;
}
int cantidad_de_parametros(char** linea)
{
	return (cantidad_de_palabras(linea) -1);
}

CMD* sacar_comando (char* name)
{
	for(int i=0; _cmd[i].name; i++)
	{
		if (strcmp (name, _cmd[i].name) == 0)
			return (&_cmd[i]);
	}
	  return ((CMD *)NULL);
}

bool buscar_comando(char* nombre_comando)
{
	for(int i=0; _cmd[i].name; i++)
	{
		if (strcmp (nombre_comando, _cmd[i].name) == 0)
			return true;
	}
	  return false;
}
void ejecutar_comando(int conexion, char** linea, int cant_parametros)
{
	CMD* comando = sacar_comando(linea[0]);

	switch(cant_parametros)
	{
		case 4:
			( (*(comando->f)) (conexion, linea[1], linea[2], linea[3], linea[4]) );
			break;

		case 3:
			( (*(comando->f)) (conexion, linea[1], linea[2], linea[3]) );
			break;

		case 2:
			( (*(comando->f)) (conexion, linea[1], linea[2]) );
			break;

		case 1:
			( (*(comando->f)) (conexion, linea[1]) );
			break;

		case 0:
			( (*(comando->f)) (conexion) );
			break;
	}

}

bool hacer_pruebas(char* nombre_comando, int cant_parametros)
{
	bool existe_comando = buscar_comando(nombre_comando);
	if(!existe_comando)
	{
		printf("no existe comando \"%s\"  \n", nombre_comando);
		return false;
	}

	else
	{
		CMD* comando = sacar_comando(nombre_comando);
		bool cant_parametros_correctos = verificar_cant_de_parametros(comando, cant_parametros);
		if(!cant_parametros_correctos)
		{
			printf("la cantidad de parametros no es correcto \n");
			return false;
		}
		else
		{
			return true;
		}
	}


}

void ejecutar_linea(int conexion, char* input)
{
	char** linea = string_split(input, " ");
	int cant_parametros = cantidad_de_parametros(linea);

	bool paso_pruebas = hacer_pruebas(linea[0], cant_parametros);

	if(paso_pruebas)
		ejecutar_comando(conexion, linea, cant_parametros);  //		((*(comando->f)) (conexion_nueva, "eric", "pollos copacabana"));
	else
		printf("no se pudo realizar el comando  \n");

}
//===================================================================


//======================  AGREGAR TAB  ==============================
char *command_generator ();
char **fileman_completion ();
char* dupstr ();

// Tell the GNU Readline library how to complete.  We want to try to complete
//   on command names if this is the first word in the line, or on filenames
//   if not.
void agregar_funcion_tab ()
{
  // Allow conditional parsing of the ~/.inputrc file.
  rl_readline_name = " ESTA SI";

  // Tell the completer that we want a crack first. //
  rl_attempted_completion_function = (CPPFunction *)fileman_completion;
}

// Attempt to complete on the contents of TEXT.  START and END show the
//   region of TEXT that contains the word to complete.  We can use the
//   entire line in case we want to do some simple parsing.  Return the
//  array of matches, or NULL if there aren't any.
char** fileman_completion (char* text,int start,int end)
{
  char **matches;

  matches = (char **)NULL;

// If this word is at the start of the line, then it is a command
//     to complete.  Otherwise it is the name of a file in the current
//     directory.
  if (start == 0)
	  matches = completion_matches (text, command_generator);

  return (matches);
}

// Generator function for command completion.  STATE lets us know whether
//   to start from scratch; without any state (i.e. STATE == 0), then we
//   start at the top of the list.
char* command_generator (char* text, int state)
{
  static int list_index, len;
  char *name;

// If this is a new word to complete, initialize now.  This includes
//     saving the length of TEXT for efficiency, and initializing the index
//     variable to 0.
  if (!state)
    {
      list_index = 0;
      len = strlen (text);
    }

  // Return the next name which partially matches from the command list.
  while (name = _cmd[list_index].name)
    {
      list_index++;

      if (strncmp (name, text, len) == 0)
        return (dupstr(name));
    }

  // If no names matched, then return NULL.
  return ((char *)NULL);
}

char* dupstr (char* s)
{
  char *r;

  r = malloc (strlen (s) + 1);
  strcpy (r, s);
  return (r);
}
//====================================================================================

//==============================  FUNCIONES DE COMANDO ===============================

void por_default()
{
	printf("estas en el dafault");
}





//==================   QUITAR ESPACIO FINAL  ==============================
char* nueva_palabra(char* input)
{
	int largo_input = strlen(input);
	char* palabra = malloc(largo_input);

	for(int i=0; i< largo_input -1; i++)
	{
		palabra[i] = input[i];
	}
	palabra[largo_input -1] = '\0';

	return palabra;
}

char* quitar_ultimo_espacio(char* input)
{
	int largo_input = strlen(input);

	if(input[largo_input -1] == ' ') //si tiene espacio o no
	{
		char* palabra = nueva_palabra(input);
		free(input);
		return palabra;
	}
	else
	{
		return input;
	}

}


