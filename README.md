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

## 3. Compilação e execução

Na pasta do projeto, compile o programa com GCC:

```sh
gcc -std=c11 -Wall -Wextra -Werror main.c lexer.c -o lexer
```

Passe o caminho do arquivo de entrada como argumento:

```sh
./lexer exemplo01.txt
```

Para testar os outros exemplos:

```sh
./lexer exemplo02.txt
./lexer exemplo03.txt
```

O programa imprime cada token no formato `<TIPO, "LEXEMA", INDICE>`, incluindo `TOKEN_EOF` ao final. Se encontrar um caractere não reconhecido, imprime um token `ERRO` e termina com código de saída diferente de zero.

## 4. Arquivos de exemplo

- `exemplo01.txt`: expressão aritmética com parênteses, números, operadores e espaços em branco.
- `exemplo02.txt`: arquivo vazio, para verificar o tratamento imediato do fim de arquivo.
- `exemplo03.txt`: expressão com caracteres não reconhecidos, para verificar a geração de tokens `ERRO`.

## 5. Organização dos arquivos

- `lexer.h`: tipos `Token` e `Lexer` e declaração da função `proximoToken`.
- `lexer.c`: implementação do analisador léxico.
- `main.c`: integração do analisador léxico, leitura do arquivo de entrada e exibição dos tokens.
- `exemplo01.txt`, `exemplo02.txt` e `exemplo03.txt`: arquivos de entrada para teste.
