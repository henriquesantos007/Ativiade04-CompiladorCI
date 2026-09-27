#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum {
	ABRE_PAR,
	FECHA_PAR,
	NUM,
	OP,
    EOF
} TipoToken;

typedef struct {
	TipoToken tipo;
	char *lexema;
	size_t indice;
} Token;


int main(){


    return 0;
}