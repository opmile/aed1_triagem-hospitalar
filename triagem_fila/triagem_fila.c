#include "triagem_fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    Paciente paciente;
    struct No* prox;
} No;

struct FilaTriagem {
    No* inicio;
    size_t tamanho;
};

static No* no_criar(Paciente paciente) {
    No* no = (No*)malloc(sizeof(No));
    if (!no) return NULL;
    no->paciente = paciente;
    no->prox = NULL;
    return no;
}

FilaTriagem* fila_triagem_criar(void) {
    FilaTriagem* fila = (FilaTriagem*)malloc(sizeof(FilaTriagem));
    if (!fila) return NULL;
    fila->inicio = NULL;
    fila->tamanho = 0;
    return fila;
}

void fila_triagem_destruir(FilaTriagem* fila) {
    if (!fila) return;

    No* atual = fila->inicio;
    while (atual) {
        No* prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(fila);
}

int fila_triagem_vazia(const FilaTriagem* fila) {
    return (!fila || fila->tamanho == 0) ? 1 : 0;
}

size_t fila_triagem_tamanho(const FilaTriagem* fila) {
    return fila ? fila->tamanho : 0;
}

int fila_triagem_inserir(FilaTriagem* fila, Paciente paciente) {
    if (!fila) return 0;

    No* novo = no_criar(paciente);
    if (!novo) return 0;

    /* Lista vazia ou novo tem prioridade maior que o primeiro -> entra no início */
    if (!fila->inicio || paciente.prioridade > fila->inicio->paciente.prioridade) {
        novo->prox = fila->inicio;
        fila->inicio = novo;
        fila->tamanho++;
        return 1;
    }

    /*
     * Inserção estável:
     * Avança enquanto o próximo tiver prioridade MAIOR ou IGUAL à do novo.
     * Assim, em empate, o novo entra depois dos já existentes (ordem de chegada).
     */
    No* atual = fila->inicio;
    while (atual->prox && atual->prox->paciente.prioridade >= paciente.prioridade) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    fila->tamanho++;
    return 1;
}

int fila_triagem_espiar(const FilaTriagem* fila, Paciente* out_paciente) {
    if (!fila || !out_paciente || !fila->inicio) return 0;
    *out_paciente = fila->inicio->paciente;
    return 1;
}

int fila_triagem_atender_proximo(FilaTriagem* fila, Paciente* out_paciente) {
    if (!fila || !fila->inicio) return 0;

    No* primeiro = fila->inicio;
    if (out_paciente) {
        *out_paciente = primeiro->paciente;
    }

    fila->inicio = primeiro->prox;
    free(primeiro);
    fila->tamanho--;
    return 1;
}

void fila_triagem_imprimir(const FilaTriagem* fila) {
    if (!fila) {
        printf("(fila inexistente)\n");
        return;
    }

    if (!fila->inicio) {
        printf("(fila vazia)\n");
        return;
    }

    printf("Fila de triagem (tamanho=%zu):\n", fila->tamanho);
    const No* atual = fila->inicio;
    while (atual) {
        printf("  [prio=%d] id=%d nome=%s\n",
               atual->paciente.prioridade,
               atual->paciente.id,
               atual->paciente.nome);
        atual = atual->prox;
    }
}

void fila_triagem_listar_pacientes(const FilaTriagem* fila) {
    if (!fila) {
        printf("(fila inexistente)\n");
        return;
    }

    if (!fila->inicio) {
        printf("(fila vazia)\n");
        return;
    }

    printf("Pacientes aguardando atendimento (ordem de prioridade):\n");
    const No* atual = fila->inicio;
    while (atual) {
        printf("  [prio=%d] id=%d nome=%s\n",
               atual->paciente.prioridade,
               atual->paciente.id,
               atual->paciente.nome);
        atual = atual->prox;
    }
}
