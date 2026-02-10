#include <stdio.h>

#include "triagem_fila/triagem_fila.h"
#include "triagem_fila/triagem_menu.h"
#include "prontuario/prontuario.h"
#include "prontuario/prontuario_menu.h"
#include "utils/io_utils.h"

int main(void) {
    FilaTriagem* fila = fila_triagem_criar();
    if (!fila) {
        fprintf(stderr, "Erro: falha ao criar fila de triagem.\n");
        return 1;
    }

    Prontuario* prontuario = prontuario_criar();
    if (!prontuario) {
        fprintf(stderr, "Erro: falha ao criar prontuário.\n");
        fila_triagem_destruir(fila);
        return 1;
    }

    int opcao = -1;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1) Triagem\n");
        printf("2) Prontuário\n");
        printf("0) Sair\n");

        if (!ler_int("Opção: ", &opcao)) {
            printf("Entrada inválida.\n");
            continue;
        }

        switch (opcao) {
            case 0:
                break;
            case 1:
                menu_triagem(fila);
                break;
            case 2:
                menu_prontuario(prontuario);
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }

    } while (opcao != 0);

    prontuario_destruir(prontuario);
    fila_triagem_destruir(fila);
    return 0;
}
