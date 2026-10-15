#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

Lexer inicializaLexer(const char *buffer) {
	Lexer lexer;
	lexer.buffer = buffer;
	lexer.indice = 0;
	return lexer;
}

// Funções auxiliares

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

// Função específica para ler números que podem ter mais de 1 caractere. Retorna o token corretamente estruturado
Token lerNumero(Lexer *lexer) {
	size_t inicio = (size_t)lexer->indice;

	while (!fimBuffer(lexer) &&
		isdigit((unsigned char)lexer->buffer[lexer->indice])) {
		lexer->indice++;
	}

	size_t tamanho = (size_t)lexer->indice - inicio; // Encontra o tamanho em caracteres do número
	Token token = {NUM, malloc(tamanho + 1), inicio};  // Aloca para o lexema o tamanho do caracteres do respectivo número no código fonte
	if (token.lexema == NULL) {
		token.tipo = ERRO;
		return token;
	}
	memcpy(token.lexema, lexer->buffer + inicio, tamanho); // Faz a cópia da string do número para o lexema do token
	token.lexema[tamanho] = '\0';

	return token;
}

// Função de resgate dos tokens
Token proximoToken(Lexer *lexer) {
	ignorarEspaco(lexer); // Ignora espaços ou caracteres irrelevantes para a compilação
	size_t indice = (size_t)lexer->indice;
	TipoToken tipo;

    // Retornar Token de erro caso seja o fim do buffer
	if (fimBuffer(lexer)) {
		Token token = {TOKEN_EOF, malloc(1), indice};
		if (token.lexema != NULL) {
			token.lexema[0] = '\0';
		} else {
			token.tipo = ERRO;
		}
		return token;
	}


	char caractere = lexer->buffer[lexer->indice];

    // Aplica a função exclusiva de lerNumero para caracteres numéricos
	if (isdigit((unsigned char)caractere)) {
		return lerNumero(lexer);
	}

    // Segue para definir outras opções de tipos de tokens
	switch (caractere) {
		case '(':
			tipo = ABRE_PAR;
			break;
		case ')':
			tipo = FECHA_PAR;
			break;
		case '+':
		case '-':
		case '/':
		case '*':
			tipo = OP;
			break;
		default: {
			Token token = {ERRO, malloc(2), indice}; // Token de erro caso encontre um caractere que não foi mapeado
			lexer->indice++;
			if (token.lexema != NULL) {
				token.lexema[0] = caractere;
				token.lexema[1] = '\0';
			}
			return token;
		}
	}

    // Estruturação do retorno do token
	Token token = {tipo, malloc(2), indice};
	lexer->indice++;
	if (token.lexema == NULL) {
		token.tipo = ERRO;
		return token;
	}
	token.lexema[0] = caractere;
	token.lexema[1] = '\0';
    
	return token;
}