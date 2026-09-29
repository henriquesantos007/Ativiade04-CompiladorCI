# Atividade 04 — Compilador EC1 (Expressões Constantes)

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

O resultado é uma árvore de sintaxe abstrata (`ast.h`/`ast.c`), com nós de constante (`NO_CONST`) e de operação binária (`NO_OPBIN`). Qualquer erro léxico ou sintático encontrado durante a análise é reportado em `stderr` e encerra o programa com código de saída diferente de zero. A implementação do interpretador (avaliação do valor da expressão) fica para uma etapa seguinte.

## 4. Compilação e execução

Na pasta do projeto, compile o programa com GCC:

```sh
gcc -std=c11 -Wall -Wextra -Werror main.c lexer.c parser.c ast.c -o compilador
```

Passe o caminho do arquivo de entrada como argumento:

```sh
./compilador exemplo01.txt
```

Para testar os outros exemplos:

```sh
./compilador exemplo02.txt
./compilador exemplo03.txt
./compilador exemplo04.txt
```

O programa imprime cada token no formato `<TIPO, "LEXEMA", INDICE>`, incluindo `TOKEN_EOF` ao final, e em seguida a árvore sintática do programa (quando a análise sintática é bem-sucedida). Se encontrar um caractere não reconhecido ou uma estrutura sintática inválida, imprime uma mensagem de erro e termina com código de saída diferente de zero.

## 5. Arquivos de exemplo

- `exemplo01.txt`: expressão com operadores fora do formato totalmente parentetizado exigido pela gramática EC1 — válida lexicamente, mas rejeitada pela análise sintática.
- `exemplo02.txt`: arquivo vazio, para verificar o tratamento imediato do fim de arquivo.
- `exemplo03.txt`: expressão com caracteres não reconhecidos, para verificar a geração de tokens `ERRO`.
- `exemplo04.txt`: expressão válida segundo a gramática EC1, para verificar a árvore sintática gerada.

## 6. Organização dos arquivos

- `lexer.h` / `lexer.c`: tipos `Token` e `Lexer`, e implementação do analisador léxico.
- `ast.h` / `ast.c`: estrutura da árvore de sintaxe abstrata (`Exp`) e funções auxiliares (`criaConst`, `criaOpBin`, `liberaExp`, `imprimeExp`).
- `parser.h` / `parser.c`: analisador sintático descendente recursivo (`analisaPrograma`, `analisaExpressao`, `analisaOperador`).
- `main.c`: leitura do arquivo de entrada, exibição dos tokens e da árvore sintática.
- `exemplo01.txt` a `exemplo04.txt`: arquivos de entrada para teste.

## 7. Uso de LLMs

Parte da implementação da análise sintática (`ast.h`, `ast.c`, `parser.h`, `parser.c`) e a integração em `main.c` foram feitas com apoio do Claude Code, a partir do material da disciplina (gramática da linguagem EC1 e algoritmo de análise descendente recursiva descritos no documento da Atividade 04). O código gerado foi revisado antes do commit.
