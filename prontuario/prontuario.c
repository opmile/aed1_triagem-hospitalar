#include "prontuario.h"

#include <stdlib.h>

typedef struct NoAtendimento {
    Atendimento atendimento;
    struct NoAtendimento* prox;
} NoAtendimento;

struct Prontuario {
    NoAtendimento* inicio;
    NoAtendimento* fim;
    size_t tamanho;
};

static NoAtendimento* no_criar(Atendimento atendimento) {
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

size_t prontuario_tamanho(const Prontuario* prontuario) {
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
