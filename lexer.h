#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
	ABRE_PAR,
	FECHA_PAR,
	NUM,
	OP,
	TOKEN_EOF,
	ERRO
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

Lexer inicializaLexer(const char *buffer);
Token proximoToken(Lexer *lexer);

#endif
