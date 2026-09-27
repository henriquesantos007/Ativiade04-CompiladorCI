#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

const char *nomeTipoToken(TipoToken tipo) {
    switch (tipo) {
        case ABRE_PAR:
            return "ABRE_PAR";
        case FECHA_PAR:
            return "FECHA_PAR";
        case NUM:
            return "NUM";
        case OP:
            return "OP";
        case TOKEN_EOF:
            return "TOKEN_EOF";
        case ERRO:
            return "ERRO";
        default:
            return "DESCONHECIDO";
    }
}

int main( int argc, char *argv[]){

    //Verifica a quantidade de argumentos
    if (argc != 2) {
    printf("Uso: %s <arquivo>\n", argv[0]);
    return 1;
    }

    //Abre o arquivo
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
    }

    //verifica o tamanho do arquivo 
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    //reserva memória para o conteúdo do arquivo
    char *buffer = malloc((tamanho + 1) * sizeof(char));
    if (buffer == NULL) {
    printf("Erro ao alocar memória.\n");
    fclose(arquivo);
    return 1;
    }

    //Ler o conteúdo do arquivo
    size_t lidos = fread(buffer, sizeof(char), tamanho, arquivo);
    buffer[lidos] = '\0';

    Lexer lexer = inicializaLexer(buffer);

    Token token;

    do {
        token = proximoToken(&lexer);

        printf("<%s, \"%s\", %zu>\n",
            nomeTipoToken(token.tipo),
            token.lexema,
            token.indice);

        free(token.lexema);

    } while (token.tipo != TOKEN_EOF && token.tipo != ERRO);

    int codigoSaida = 0;

    if (token.tipo == ERRO) {
        codigoSaida = 1;
    }

    fclose(arquivo);
    free(buffer);



    return codigoSaida;
}