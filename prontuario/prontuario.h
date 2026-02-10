#ifndef PRONTUARIO_H
#define PRONTUARIO_H

#include <stddef.h> /* size_t */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * TAD: Prontuário Médico
 *
 * Estrutura: lista encadeada simples para armazenar o histórico de atendimentos
 * de um paciente (em ordem de inserção).
 */

typedef struct {
    int id_atendimento;         /* identificador do atendimento */
    char data[11];              /* "DD/MM/AAAA" (10 + '\0') */
    char descricao[256];        /* resumo do atendimento */
} Atendimento;

/* Tipo opaco (encapsulamento) */
typedef struct Prontuario Prontuario;

/* Cria um prontuário vazio. Retorna NULL em caso de falha de memória. */
Prontuario* prontuario_criar(void);

/* Libera toda a memória do prontuário (nós + estrutura). */
void prontuario_destruir(Prontuario* prontuario);

/* Retorna 1 se vazio, 0 caso contrário. */
int prontuario_vazio(const Prontuario* prontuario);

/* Retorna a quantidade de atendimentos armazenados. */
size_t prontuario_tamanho(const Prontuario* prontuario);

/*
 * Insere um atendimento no final do histórico.
 * Retorna 1 se inseriu, 0 se falhou (memória).
 */
int prontuario_adicionar(Prontuario* prontuario, Atendimento atendimento);

/*
 * Consulta o primeiro atendimento (mais antigo) sem removê-lo.
 * Retorna 1 se existe, 0 se prontuário vazio.
 */
int prontuario_primeiro(const Prontuario* prontuario, Atendimento* out_atendimento);

/*
 * Consulta o último atendimento (mais recente) sem removê-lo.
 * Retorna 1 se existe, 0 se prontuário vazio.
 */
int prontuario_ultimo(const Prontuario* prontuario, Atendimento* out_atendimento);

/*
 * Percorre todos os atendimentos chamando um callback.
 * Se callback == NULL, não faz nada.
 */
void prontuario_para_cada(const Prontuario* prontuario,
                          void (*callback)(const Atendimento* atendimento, void* ctx),
                          void* ctx);

/* Imprime todos os atendimentos em ordem cronológica (do mais antigo ao mais recente). */
void prontuario_imprimir(const Prontuario* prontuario);

/*
 * Busca atendimentos por data (comparação exata com o campo data).
 * Retorna a quantidade de atendimentos encontrados.
 */
size_t prontuario_buscar_por_data(const Prontuario* prontuario, const char* data);

/*
 * Busca atendimentos por palavra-chave na descrição (case-sensitive).
 * Retorna a quantidade de atendimentos encontrados.
 */
size_t prontuario_buscar_por_palavra_chave(const Prontuario* prontuario, const char* palavra);

#ifdef __cplusplus
}
#endif

#endif /* PRONTUARIO_H */
