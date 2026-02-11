#ifndef TRIAGEM_FILA_H
#define TRIAGEM_FILA_H

 //TAD: Fila de Triagem (lista encadeada ordenada por prioridade)
 
 
 // valor de prioridade maior = atendimento mais urgente 
 // em caso de empate fila preserva a ordem de chegada 


typedef struct {
    int id;                 
    char nome[101];         
    int prioridade;        
} Paciente;

typedef struct FilaTriagem FilaTriagem;

FilaTriagem* fila_triagem_criar(void);

void fila_triagem_destruir(FilaTriagem* fila);

int fila_triagem_vazia(const FilaTriagem* fila);

int fila_triagem_tamanho(const FilaTriagem* fila);

int fila_triagem_inserir(FilaTriagem* fila, Paciente paciente);

int fila_triagem_espiar(const FilaTriagem* fila, Paciente* out_paciente);

int fila_triagem_atender_proximo(FilaTriagem* fila, Paciente* out_paciente);

void fila_triagem_imprimir(const FilaTriagem* fila);

void fila_triagem_listar_pacientes(const FilaTriagem* fila);

#endif 
