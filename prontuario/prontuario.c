#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "prontuario.h"

typedef struct NoAtendimento {
    Atendimento atendimento;
    struct NoAtendimento* prox;
} NoAtendimento;

struct Prontuario {
    NoAtendimento* inicio;
    NoAtendimento* fim;
    size_t tamanho;
};

 NoAtendimento* no_criar(Atendimento atendimento) {
    NoAtendimento* no = (NoAtendimento*)malloc(sizeof(NoAtendimento));
    if (!no) return NULL;
    no->atendimento = atendimento;
    no->prox = NULL;
    return no;
}

Prontuario* prontuario_criar(void) {
    Prontuario* p = (Prontuario*)malloc(sizeof(Prontuario));
    if (!p) return NULL;
    p->inicio = NULL;
    p->fim = NULL;
    p->tamanho = 0;
    return p;
}

void prontuario_destruir(Prontuario* prontuario) {
    if (!prontuario) return;

    NoAtendimento* atual = prontuario->inicio;
    while (atual) {
        NoAtendimento* prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(prontuario);
}

int prontuario_vazio(const Prontuario* prontuario) {
    return (!prontuario || prontuario->tamanho == 0) ? 1 : 0;
}

int prontuario_tamanho(const Prontuario* prontuario) {
    return prontuario ? prontuario->tamanho : 0;
}

int prontuario_adicionar(Prontuario* prontuario, Atendimento atendimento) {
    if (!prontuario) return 0;

    NoAtendimento* novo = no_criar(atendimento);
    if (!novo) return 0;

    if (!prontuario->inicio) {
        prontuario->inicio = novo;
        prontuario->fim = novo;
    } else {
        prontuario->fim->prox = novo;
        prontuario->fim = novo;
    }

    prontuario->tamanho++;
    return 1;
}

int prontuario_primeiro(const Prontuario* prontuario, Atendimento* out_atendimento) {
    if (!prontuario || !out_atendimento || !prontuario->inicio) return 0;
    *out_atendimento = prontuario->inicio->atendimento;
    return 1;
}

int prontuario_ultimo(const Prontuario* prontuario, Atendimento* out_atendimento) {
    if (!prontuario || !out_atendimento || !prontuario->fim) return 0;
    *out_atendimento = prontuario->fim->atendimento;
    return 1;
}

void prontuario_para_cada(const Prontuario* prontuario,
                          void (*callback)(const Atendimento* atendimento, void* ctx),
                          void* ctx) {
    if (!prontuario || !callback) return;

    const NoAtendimento* atual = prontuario->inicio;
    while (atual) {
        callback(&atual->atendimento, ctx);
        atual = atual->prox;
    }
}

void atendimento_imprimir(const Atendimento* a) {
    printf("- Atendimento %d | Data: %s\n", a->id_atendimento, a->data);
    printf("  Descrição: %s\n", a->descricao);
}

void prontuario_imprimir(const Prontuario* prontuario) {
    if (!prontuario) {
        printf("(prontuário inexistente)\n");
        return;
    }

    if (!prontuario->inicio) {
        printf("(prontuário vazio)\n");
        return;
    }

    printf("Histórico de atendimentos (total=%zu):\n", prontuario->tamanho);
    const NoAtendimento* atual = prontuario->inicio;
    while (atual) {
        atendimento_imprimir(&atual->atendimento);
        atual = atual->prox;
    }
}

int prontuario_buscar_por_data(const Prontuario* prontuario, const char* data) {
    if (!prontuario || !data) return 0;

    size_t encontrados = 0;
    const NoAtendimento* atual = prontuario->inicio;

    while (atual) {
        if (strcmp(atual->atendimento.data, data) == 0) {
            atendimento_imprimir(&atual->atendimento);
            encontrados++;
        }
        atual = atual->prox;
    }

    return encontrados;
}

intt prontuario_buscar_por_palavra_chave(const Prontuario* prontuario, const char* palavra) {
    if (!prontuario || !palavra) return 0;

    intt encontrados = 0;
    const NoAtendimento* atual = prontuario->inicio;

    while (atual) {
        if (strstr(atual->atendimento.descricao, palavra) != NULL) {
            atendimento_imprimir(&atual->atendimento);
            encontrados++;
        }
        atual = atual->prox;
    }

    return encontrados;
}
