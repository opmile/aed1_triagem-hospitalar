#include "triagem_menu.h"

#include <stdio.h>

#include "../utils/io_utils.h"

void menu_triagem(FilaTriagem* fila) {
    int proximo_id = 1;
    int opcao = -1;

    do {
        printf("\n=== Menu: Triagem ===\n");
        printf("1) Inserir paciente\n");
        printf("2) Listar pacientes (ordem de prioridade)\n");
        printf("3) Atender próximo (remover maior prioridade)\n");
        printf("0) Voltar\n");

        if (!ler_int("Opção: ", &opcao)) {
            printf("Entrada inválida.\n");
            continue;
        }

        switch (opcao) {
            case 0:
                break;

            case 1: {
                Paciente p;
                p.id = proximo_id++;

                ler_linha("Nome: ", p.nome, sizeof(p.nome));
                if (p.nome[0] == '\0') {
                    printf("Nome inválido.\n");
                    proximo_id--; /* desfaz id */
                    break;
                }

                if (!ler_int("Prioridade (maior = mais urgente): ", &p.prioridade)) {
                    printf("Prioridade inválida.\n");
                    proximo_id--; /* desfaz id */
                    break;
                }

                if (!fila_triagem_inserir(fila, p)) {
                    printf("Falha ao inserir (memória).\n");
                    proximo_id--; /* desfaz id */
                    break;
                }

                printf("Paciente inserido na fila.\n");
                break;
            }

            case 2:
                fila_triagem_listar_pacientes(fila);
                break;

            case 3: {
                Paciente p;
                if (!fila_triagem_atender_proximo(fila, &p)) {
                    printf("Fila vazia.\n");
                } else {
                    printf("Encaminhado para atendimento: [prio=%d] id=%d nome=%s\n",
                           p.prioridade, p.id, p.nome);
                }
                break;
            }

            default:
                printf("Opção inválida.\n");
                break;
        }

    } while (opcao != 0);
}
