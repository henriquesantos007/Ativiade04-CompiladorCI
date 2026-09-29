#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

// Reporta um erro (léxico ou sintático) encontrado durante a análise e encerra o programa
static void erroSintatico(Parser *parser, const char *mensagem) {
	fprintf(stderr, "Erro sintatico na posicao %zu: %s (token \"%s\")\n",
		parser->atual.indice, mensagem, parser->atual.lexema);
	exit(1);
}

// Libera o token atual e busca o próximo token do lexer
static void avanca(Parser *parser) {
	free(parser->atual.lexema);
	parser->atual = proximoToken(parser->lexer);
}

Parser inicializaParser(Lexer *lexer) {
	Parser parser;
	parser.lexer = lexer;
	parser.atual = proximoToken(lexer);
	return parser;
}

Operador analisaOperador(Parser *parser) {
	if (parser->atual.tipo == ERRO) {
		erroSintatico(parser, "caractere nao reconhecido pelo analisador lexico");
	}
	if (parser->atual.tipo != OP) {
		erroSintatico(parser, "esperado um operador (+, -, * ou /)");
	}

	Operador op;
	switch (parser->atual.lexema[0]) {
		case '+':
			op = OP_SOMA;
			break;
		case '-':
			op = OP_SUB;
			break;
		case '*':
			op = OP_MULT;
			break;
		case '/':
			op = OP_DIV;
			break;
		default:
			erroSintatico(parser, "operador desconhecido");
			op = OP_SOMA; // inalcançável: erroSintatico encerra o programa
	}

	avanca(parser);
	return op;
}

Exp *analisaExpressao(Parser *parser) {
	if (parser->atual.tipo == ERRO) {
		erroSintatico(parser, "caractere nao reconhecido pelo analisador lexico");
	}

	if (parser->atual.tipo == NUM) {
		int valor = atoi(parser->atual.lexema);
		avanca(parser);
		return criaConst(valor);
	}

	if (parser->atual.tipo == ABRE_PAR) {
		avanca(parser);

		Exp *esq = analisaExpressao(parser);
		Operador op = analisaOperador(parser);
		Exp *dir = analisaExpressao(parser);

		if (parser->atual.tipo != FECHA_PAR) {
			erroSintatico(parser, "esperado ')' para fechar a expressao");
		}
		avanca(parser);

		return criaOpBin(op, esq, dir);
	}

	if (parser->atual.tipo == TOKEN_EOF) {
		erroSintatico(parser, "fim inesperado da entrada, esperava-se uma expressao");
	}

	erroSintatico(parser, "esperado um numero ou '(' para iniciar uma expressao");
	return NULL; // inalcançável: erroSintatico encerra o programa
}

Exp *analisaPrograma(Parser *parser) {
	Exp *arvore = analisaExpressao(parser);

	if (parser->atual.tipo != TOKEN_EOF) {
		erroSintatico(parser, "tokens inesperados apos o fim do programa");
	}

	return arvore;
}
