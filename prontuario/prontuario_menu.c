#include <stdio.h>

#include "prontuario_menu.h"
#include "../utils/io_utils.h"

void menu_prontuario(Prontuario* prontuario) {
    int proximo_id_atendimento = 1;
    int opcao = -1;

    do {
        printf("\n=== Menu: Prontuário ===\n");
        printf("1) Registrar atendimento\n");
        printf("2) Visualizar histórico completo\n");
        printf("3) Buscar por data\n");
        printf("4) Buscar por palavra-chave\n");
        printf("0) Voltar\n");

        if (!ler_int("Opção: ", &opcao)) {
            printf("Entrada inválida.\n");
            continue;
        }

        switch (opcao) {
            case 0:
                break;

            case 1: {
                Atendimento a;
                a.id_atendimento = proximo_id_atendimento++;

                ler_linha("Data (DD/MM/AAAA): ", a.data, sizeof(a.data));
                if (a.data[0] == '\0') {
                    printf("Data inválida.\n");
                    proximo_id_atendimento--; 
                    break;
                }

                ler_linha("Descrição: ", a.descricao, sizeof(a.descricao));
                if (a.descricao[0] == '\0') {
                    printf("Descrição inválida.\n");
                    proximo_id_atendimento--; 
                    break;
                }

                if (!prontuario_adicionar(prontuario, a)) {
                    printf("Falha ao registrar (memória).\n");
                    proximo_id_atendimento--; 
                    break;
                }

                printf("Atendimento registrado.\n");
                break;
            }

            case 2:
                prontuario_imprimir(prontuario);
                break;

            case 3: {
                char data[11];
                ler_linha("Data (DD/MM/AAAA): ", data, sizeof(data));
                int qtd = prontuario_buscar_por_data(prontuario, data);
                printf("Encontrados: %d\n", qtd);
                break;
            }

            case 4: {
                char palavra[101];
                ler_linha("Palavra-chave: ", palavra, sizeof(palavra));
                int qtd = prontuario_buscar_por_palavra_chave(prontuario, palavra);
                printf("Encontrados: %d\n", qtd);
                break;
            }

            default:
                printf("Opção inválida.\n");
                break;
        }

    } while (opcao != 0);
}
