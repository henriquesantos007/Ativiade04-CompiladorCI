#include "gerador.h"

static int operadorValido(Operador op) {
	switch (op) {
		case OP_SOMA:
		case OP_SUB:
		case OP_MULT:
		case OP_DIV:
			return 1;
		default:
			return 0;
	}
}

static int expressaoValida(const Exp *exp) {
	if (exp == NULL) {
		return 0;
	}

	switch (exp->tipo) {
		case NO_CONST:
			return 1;
		case NO_OPBIN:
			return operadorValido(exp->dados.opbin.op) &&
				expressaoValida(exp->dados.opbin.esq) &&
				expressaoValida(exp->dados.opbin.dir);
		default:
			return 0;
	}
}

static int emitirExpressao(const Exp *exp, FILE *saida) {
	if (exp->tipo == NO_CONST) {
		return fprintf(saida, "\tmovq $%d, %%rax\n", exp->dados.valor) < 0 ? -1 : 0;
	}

	if (emitirExpressao(exp->dados.opbin.dir, saida) != 0 ||
		fprintf(saida, "\tpushq %%rax\n") < 0 ||
		emitirExpressao(exp->dados.opbin.esq, saida) != 0 ||
		fprintf(saida, "\tpopq %%rbx\n") < 0) {
		return -1;
	}

	switch (exp->dados.opbin.op) {
		case OP_SOMA:
			return fprintf(saida, "\taddq %%rbx, %%rax\n") < 0 ? -1 : 0;
		case OP_SUB:
			return fprintf(saida, "\tsubq %%rbx, %%rax\n") < 0 ? -1 : 0;
		case OP_MULT:
			return fprintf(saida, "\timulq %%rbx, %%rax\n") < 0 ? -1 : 0;
		case OP_DIV:
			return fprintf(saida,
				"\tcqto\n"
				"\tidivq %%rbx\n") < 0 ? -1 : 0;
		default:
			return -1;
	}
}

int gerar_codigo_ast(const Exp *exp, FILE *saida) {
	if (!expressaoValida(exp) || saida == NULL) {
		return -1;
	}

	if (fprintf(saida,
		"\t.section .text\n"
		"\t.globl _start\n"
		"_start:\n") < 0 ||
		emitirExpressao(exp, saida) != 0 ||
		fprintf(saida,
			"\tcall imprime_num\n"
			"\tcall sair\n"
			"\t.include \"runtime.s\"\n") < 0 ||
		ferror(saida)) {
		return -1;
	}

	return 0;
}
