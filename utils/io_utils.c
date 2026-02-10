#include "io_utils.h"

#include <stdio.h>
#include <string.h>

static void descartar_resto_da_linha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta */
    }
}

void ler_linha(const char* prompt, char* buf, size_t buf_sz) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }

    while (1) {
        if (!fgets(buf, (int)buf_sz, stdin)) {
            buf[0] = '\0';
            return;
        }

        /* se a leitura estourou o buffer, descarta o resto da linha */
        if (strchr(buf, '\n') == NULL) {
            descartar_resto_da_linha();
        }

        buf[strcspn(buf, "\n")] = '\0';

        /* se veio vazio (ex.: só Enter ou newline pendente), pede de novo */
        if (buf[0] != '\0') {
            return;
        }

        /* se o usuário só apertou Enter, reimprime o prompt para ficar claro */
        if (prompt) {
            printf("%s", prompt);
            fflush(stdout);
        }
    }
}

int ler_int(const char* prompt, int* out) {
    char linha[64];

    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }

    if (!fgets(linha, (int)sizeof(linha), stdin)) {
        return 0;
    }

    /* Se a linha não terminou com '\n', descarta o restante */
    if (strchr(linha, '\n') == NULL) {
        descartar_resto_da_linha();
    }

    return (sscanf(linha, "%d", out) == 1) ? 1 : 0;
}
