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

typedef struct {
	const char *buffer;
	int indice;
} Lexer;

Lexer inicializaLexer(const char *buffer) {
	Lexer lexer;
	lexer.buffer = buffer;
	lexer.indice = 0;
	return lexer;
}

int main(){


    return 0;
}