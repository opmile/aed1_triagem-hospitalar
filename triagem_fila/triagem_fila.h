#ifndef TRIAGEM_FILA_H
#define TRIAGEM_FILA_H

#include <stddef.h> /* size_t */

/*
 * TAD: Fila de Triagem (lista encadeada ordenada por prioridade)
 *
 * Regra de ordenação:
 *  - Maior valor de prioridade = atendimento mais urgente (vem primeiro).
 *  - Em caso de empate, a fila preserva a ordem de chegada (estável).
 */

typedef struct {
    int id;                 /* identificador do paciente (definido pelo sistema) */
    char nome[101];         /* nome do paciente (até 100 chars + '\0') */
    int prioridade;         /* nível de prioridade (ex.: 1..5 ou 0..10) */
} Paciente;

/* Tipo opaco (encapsulamento do TAD) */
typedef struct FilaTriagem FilaTriagem;

/* Cria uma fila vazia. Retorna NULL em caso de falha de memória. */
FilaTriagem* fila_triagem_criar(void);

/* Libera toda a memória da fila (nós + estrutura). */
void fila_triagem_destruir(FilaTriagem* fila);

/* Retorna 1 se vazia, 0 caso contrário. */
int fila_triagem_vazia(const FilaTriagem* fila);

/* Retorna a quantidade de pacientes na fila. */
size_t fila_triagem_tamanho(const FilaTriagem* fila);

/*
 * Insere paciente mantendo a ordenação (prioridade desc).
 * Retorna 1 se inseriu, 0 se falhou (memória).
 */
int fila_triagem_inserir(FilaTriagem* fila, Paciente paciente);

/*
 * Consulta o próximo paciente sem removê-lo.
 * Retorna 1 se existe, 0 se fila vazia.
 */
int fila_triagem_espiar(const FilaTriagem* fila, Paciente* out_paciente);

/*
 * Remove o próximo paciente (maior prioridade).
 * Retorna 1 se removeu e preenche out_paciente; 0 se fila vazia.
 */
int fila_triagem_atender_proximo(FilaTriagem* fila, Paciente* out_paciente);

/*
 * Imprime a fila (útil para depuração/menus simples).
 * O formato pode ser ajustado pela aplicação.
 */
void fila_triagem_imprimir(const FilaTriagem* fila);

/*
 * Lista (imprime) todos os pacientes aguardando atendimento, em ordem de
 * prioridade (maior -> menor). Como a estrutura interna já é uma lista
 * encadeada ordenada, a listagem é um percurso do início ao fim.
 */
void fila_triagem_listar_pacientes(const FilaTriagem* fila);

#endif /* TRIAGEM_FILA_H */
