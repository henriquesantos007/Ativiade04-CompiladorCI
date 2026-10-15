# Atividade 05 — Compilador EC1 (Geração de Código)

**Disciplina:** Construção de Compiladores — Prof. Andrei Formiga  
**Plataforma alvo:** x86-64 / Linux (GNU Assembler)

## 1. Grupo

| Nome                               | Matrícula   |
| ---------------------------------- | ----------- |
| Allan Gabriel da Cunha Vasconcelos | 20240009142 |
| Luiz Henrique Santos da Graça      | 20240008261 |
| Maria Eloiza Monteiro de Souza     | 20240008280 |
| Vinicius Victor Lopes de Almeida   | 20240008181 |

## 2. Etapa léxica

O analisador léxico lê uma expressão de um arquivo texto e a divide em tokens. Cada token exibido contém seu tipo, lexema e índice inicial no conteúdo do arquivo. Espaços, tabulações e quebras de linha são ignorados.

São reconhecidos os seguintes tokens:

| Token | Lexemas reconhecidos |
| ----- | -------------------- |
| `ABRE_PAR` | `(` |
| `FECHA_PAR` | `)` |
| `NUM` | Uma ou mais casas decimais, por exemplo `321` |
| `OP` | `+`, `-`, `*` ou `/` |
| `TOKEN_EOF` | Fim do arquivo |
| `ERRO` | Caractere não reconhecido |

## 3. Etapa sintática

A partir da sequência de tokens do lexer, o analisador sintático (`parser.h`/`parser.c`) reconhece a gramática da linguagem EC1 usando análise descendente recursiva:

```
<programa>  ::= <exp>
<expressao> ::= <num> | '(' <exp> <op> <exp> ')'
<op>        ::= '+' | '-' | '*' | '/'
```

O resultado é uma árvore de sintaxe abstrata (`ast.h`/`ast.c`), com nós de constante (`NO_CONST`) e de operação binária (`NO_OPBIN`). Qualquer erro léxico ou sintático encontrado durante a análise é reportado em `stderr` e encerra o programa com código de saída diferente de zero.

## 4. Compilação e execução

Na pasta do projeto, compile o programa com GCC:

```sh
gcc -std=c11 -Wall -Wextra -Werror \
  -Ianalise_lexica -Ianalise_sintatica -Isintese \
  main.c analise_lexica/lexer.c analise_sintatica/parser.c \
  analise_sintatica/ast.c sintese/gerador.c -o compilador
```

O modo padrão preserva a saída de tokens e da árvore sintática:

```sh
./compilador tests/exemplo04.txt
```

Para gerar um programa assembly completo, use `--asm`. A saída padrão contém
somente o assembly, então pode ser redirecionada diretamente para um arquivo:

```sh
./compilador --asm tests/exemplo04.txt > programa.s &&
as --64 programa.s -o programa.o &&
ld programa.o -o programa &&
./programa
```

Execute o comando `as` a partir da pasta do projeto para que ele encontre
`runtime.s`, incluído pelo assembly gerado. O programa montado imprime o
resultado inteiro da expressão e encerra.

Execute os testes automatizados de geração, montagem e execução com:

```sh
sh tests/test_gerador.sh
```

## 5. Arquivos de exemplo e testes

- `tests/exemplo01.txt`: expressão com operadores fora do formato totalmente parentetizado exigido pela gramática EC1 — válida lexicamente, mas rejeitada pela análise sintática.
- `tests/exemplo02.txt`: arquivo vazio, para verificar o tratamento imediato do fim de arquivo.
- `tests/exemplo03.txt`: expressão com caracteres não reconhecidos, para verificar a geração de tokens `ERRO`.
- `tests/exemplo04.txt`: expressão válida segundo a gramática EC1; também pode ser usada para gerar e executar assembly.

## 6. Organização dos arquivos

- `analise_lexica/lexer.h` / `lexer.c`: tipos `Token` e `Lexer`, e implementação do analisador léxico.
- `analise_sintatica/ast.h` / `ast.c`: estrutura da árvore de sintaxe abstrata (`Exp`) e funções auxiliares.
- `analise_sintatica/parser.h` / `parser.c`: analisador sintático descendente recursivo.
- `sintese/gerador.h` / `gerador.c`: geração recursiva de um programa assembly x86-64 completo.
- `runtime.s`: rotinas `imprime_num` e `sair`, incluídas no assembly gerado.
- `main.c`: leitura da entrada; imprime tokens e AST no modo padrão, ou assembly completo com `--asm`.
- `tests/`: expressões de exemplo para análise e geração de código.

## 7. Uso de LLMs

As etapas anteriores da análise sintática e sua integração foram desenvolvidas com apoio do Claude Code, conforme registrado na entrega da Atividade 04. A geração de assembly, o runtime e a integração do modo `--asm` foram desenvolvidos com apoio de um assistente de IA, a partir dos requisitos da Atividade 05. As alterações foram revisadas e validadas compilando, montando e executando o código gerado.
