#!/bin/sh
set -eu

raiz=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
temporario=$(mktemp -d)
trap 'rm -rf "$temporario"' EXIT HUP INT TERM

cd "$raiz"
gcc -std=c11 -Wall -Wextra -Werror \
	-Ianalise_lexica -Ianalise_sintatica -Isintese \
	main.c analise_lexica/lexer.c analise_sintatica/parser.c \
	analise_sintatica/ast.c sintese/gerador.c \
	-o "$temporario/compilador"

testar_expressao() {
	expressao=$1
	esperado=$2
	printf '%s\n' "$expressao" > "$temporario/entrada.txt"
	"$temporario/compilador" --asm "$temporario/entrada.txt" \
		> "$temporario/programa.s"
	as --64 "$temporario/programa.s" -o "$temporario/programa.o"
	ld "$temporario/programa.o" -o "$temporario/programa"
	resultado=$("$temporario/programa")
	if [ "$resultado" != "$esperado" ]; then
		printf 'Falha: %s gerou %s; esperado %s\n' \
			"$expressao" "$resultado" "$esperado" >&2
		exit 1
	fi
	printf 'OK: %s = %s\n' "$expressao" "$resultado"
}

testar_expressao '333' '333'
testar_expressao '(11 - 7)' '4'
testar_expressao '(7 - (3 + 8))' '-4'
testar_expressao '((7 - 15) / 2)' '-4'
testar_expressao '((1 + 2) * (3 + 4))' '21'

if "$temporario/compilador" --asm tests/exemplo01.txt \
	> "$temporario/invalido.s" 2> /dev/null; then
	printf 'Falha: uma expressão sintaticamente inválida foi aceita\n' >&2
	exit 1
fi
if [ -s "$temporario/invalido.s" ]; then
	printf 'Falha: houve saída assembly para uma entrada inválida\n' >&2
	exit 1
fi
printf 'OK: entrada inválida rejeitada sem emitir assembly\n'
