#include <ctype.h>
#include <string.h>
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

# Funções Auxiliares


int fimBuffer(const Lexer *lexer) {
	return lexer->buffer[lexer->indice] == '\0';
}

void ignorarEspaco(Lexer *lexer) {
	while (!fimBuffer(lexer) &&
		(lexer->buffer[lexer->indice] == ' ' ||
		 lexer->buffer[lexer->indice] == '\n' ||
		 lexer->buffer[lexer->indice] == '\t')) {
		lexer->indice++;
	}
}

Token lerNumero(Lexer *lexer) {
	size_t inicio = (size_t)lexer->indice;
	Token token;

	while (!fimBuffer(lexer) &&
		isdigit((unsigned char)lexer->buffer[lexer->indice])) {
		lexer->indice++;
	}

	size_t tamanho = (size_t)lexer->indice - inicio;
	token.tipo = NUM;
	token.indice = inicio;
	token.lexema = malloc(tamanho + 1);
	if (token.lexema != NULL) {
		memcpy(token.lexema, lexer->buffer + inicio, tamanho);
		token.lexema[tamanho] = '\0';
	}

	return token;
}

int main(){


    return 0;
}