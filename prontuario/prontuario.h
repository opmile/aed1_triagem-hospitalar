#ifndef PRONTUARIO_H
#define PRONTUARIO_H

#ifdef __cplusplus
#endif

 //TAD: Prontuário Médico
 // estrutura: lista encadeada simples (armazena historico de pacientes)

typedef struct {
    int id_atendimento;         
    char data[11];             
    char descricao[256];       
} Atendimento;


typedef struct Prontuario Prontuario;

Prontuario* prontuario_criar(void);

void prontuario_destruir(Prontuario* prontuario);

int prontuario_vazio(const Prontuario* prontuario);

int prontuario_tamanho(const Prontuario* prontuario);

int prontuario_adicionar(Prontuario* prontuario, Atendimento atendimento);

int prontuario_primeiro(const Prontuario* prontuario, Atendimento* out_atendimento);
int prontuario_ultimo(const Prontuario* prontuario, Atendimento* out_atendimento);
void prontuario_para_cada(const Prontuario* prontuario,
                          void (*callback)(const Atendimento* atendimento, void* ctx),
                          void* ctx);

void prontuario_imprimir(const Prontuario* prontuario);

int prontuario_buscar_por_data(const Prontuario* prontuario, const char* data);

int prontuario_buscar_por_palavra_chave(const Prontuario* prontuario, const char* palavra);

#ifdef __cplusplus

#endif

#endif 
