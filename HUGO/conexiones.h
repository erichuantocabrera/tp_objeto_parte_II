#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include "logs.h"
//#include <laMateLib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
	MEMALLOC,
	MEMFREE,
	MEMREAD,
	MEMWRITE,
}op_code;

#endif /* CONEXIONES_H_ */
