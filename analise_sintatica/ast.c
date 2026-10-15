#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

Exp *criaConst(int valor) {
	Exp *exp = malloc(sizeof(Exp));
	if (exp == NULL) {
		return NULL;
	}
	exp->tipo = NO_CONST;
	exp->dados.valor = valor;
	return exp;
}

Exp *criaOpBin(Operador op, Exp *esq, Exp *dir) {
	Exp *exp = malloc(sizeof(Exp));
	if (exp == NULL) {
		return NULL;
	}
	exp->tipo = NO_OPBIN;
	exp->dados.opbin.op = op;
	exp->dados.opbin.esq = esq;
	exp->dados.opbin.dir = dir;
	return exp;
}

void liberaExp(Exp *exp) {
	if (exp == NULL) {
		return;
	}
	if (exp->tipo == NO_OPBIN) {
		liberaExp(exp->dados.opbin.esq);
		liberaExp(exp->dados.opbin.dir);
	}
	free(exp);
}

char operadorParaChar(Operador op) {
	switch (op) {
		case OP_SOMA:
			return '+';
		case OP_SUB:
			return '-';
		case OP_MULT:
			return '*';
		case OP_DIV:
			return '/';
		default:
			return '?';
	}
}

void imprimeExp(Exp *exp) {
	if (exp == NULL) {
		return;
	}
	if (exp->tipo == NO_CONST) {
		printf("%d", exp->dados.valor);
	} else {
		printf("(");
		imprimeExp(exp->dados.opbin.esq);
		printf(" %c ", operadorParaChar(exp->dados.opbin.op));
		imprimeExp(exp->dados.opbin.dir);
		printf(")");
	}
}
