#include <stdio.h>
#include <string.h>

#include "triagem_fila/triagem_fila.h"

static void ler_linha(const char* prompt, char* buf, size_t buf_sz) {
    if (prompt) printf("%s", prompt);
    if (!fgets(buf, (int)buf_sz, stdin)) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

static int ler_int(const char* prompt, int* out) {
    char linha[64];
    ler_linha(prompt, linha, sizeof(linha));
    if (linha[0] == '\0') return 0;
    return (sscanf(linha, "%d", out) == 1) ? 1 : 0;
}

int main(void) {
    FilaTriagem* fila = fila_triagem_criar();
    if (!fila) {
        fprintf(stderr, "Erro: falha ao criar fila de triagem.\n");
        return 1;
    }

    int proximo_id = 1;
    int opcao = -1;

    do {
        printf("\n=== Triagem Hospitalar ===\n");
        printf("1) Inserir paciente\n");
        printf("2) Mostrar fila\n");
        printf("3) Atender próximo\n");
        printf("0) Sair\n");

        if (!ler_int("Opção: ", &opcao)) {
            printf("Entrada inválida.\n");
            continue;
        }

        switch (opcao) {
            case 0:
                /* sai no teste do while */
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
                fila_triagem_imprimir(fila);
                break;

            case 3: {
                Paciente p;
                if (!fila_triagem_atender_proximo(fila, &p)) {
                    printf("Fila vazia.\n");
                } else {
                    printf("Atendido: [prio=%d] id=%d nome=%s\n", p.prioridade, p.id, p.nome);
                }
                break;
            }

            default:
                printf("Opção inválida.\n");
                break;
        }

    } while (opcao != 0);

    fila_triagem_destruir(fila);
    return 0;
}