#ifndef AST_H
#define AST_H

typedef enum {
	OP_SOMA,
	OP_SUB,
	OP_MULT,
	OP_DIV
} Operador;

typedef enum {
	NO_CONST,
	NO_OPBIN
} TipoNo;

typedef struct Exp {
	TipoNo tipo;
	union {
		int valor; // usado quando tipo == NO_CONST
		struct {
			Operador op;
			struct Exp *esq;
			struct Exp *dir;
		} opbin; // usado quando tipo == NO_OPBIN
	} dados;
} Exp;

Exp *criaConst(int valor);
Exp *criaOpBin(Operador op, Exp *esq, Exp *dir);
void liberaExp(Exp *exp);
void imprimeExp(Exp *exp);
char operadorParaChar(Operador op);

#endif
