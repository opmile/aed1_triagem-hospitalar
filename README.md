# Sistema de Triagem Hospitalar e Prontuário Médico Dinâmico

## Visão Geral

Este projeto consiste no desenvolvimento de um **Sistema de Triagem Hospitalar e Prontuário Médico Dinâmico**, cujo objetivo é simular o funcionamento de um ambiente hospitalar de emergência. A aplicação permite o cadastro de pacientes, organização da fila de atendimento com base em critérios de prioridade e o registro de atendimentos médicos em um histórico estruturado.

O sistema foi projetado para explorar o uso de **estruturas de dados dinâmicas**, especialmente listas encadeadas, de forma alinhada aos conceitos fundamentais da disciplina de Algoritmos e Estruturas de Dados I.

## Contexto Acadêmico

* **Projeto final da disciplina:** Algoritmos e Estruturas de Dados I
* **Modalidade:** Disciplina de verão
* **Período:** 2025/4

## Objetivos do Projeto

* Aplicar conceitos teóricos de estruturas de dados em um problema prático.
* Utilizar listas encadeadas para representar estruturas dinâmicas de fila e histórico.
* Simular um processo realista de triagem hospitalar baseado em prioridade.
* Consolidar noções de complexidade, organização e manipulação eficiente de dados.

## Funcionalidades Implementadas

### Fila de Prioridade Dinâmica (Lista Encadeada Ordenada)

* **Cadastro de pacientes na fila de triagem:** pacientes são inseridos dinamicamente conforme o nível de urgência definido.
* **Atendimento do próximo paciente:** remoção do paciente com maior prioridade na fila.
* **Listagem da fila de espera:** exibição dos pacientes aguardando atendimento, respeitando a ordem de prioridade.

### Prontuário Médico (Lista Encadeada de Atendimentos)

* **Registro de atendimentos:** cada atendimento é armazenado no histórico médico do paciente.
* **Exibição do histórico médico:** visualização completa dos atendimentos realizados, em ordem cronológica.
* **Busca no prontuário:** pesquisa de atendimentos por data ou por palavra-chave.

## Estruturas de Dados Utilizadas

* **Lista encadeada ordenada:** utilizada para implementar a fila de triagem com prioridade.
* **Lista encadeada simples:** utilizada para armazenar o histórico de atendimentos de cada paciente.

Essas escolhas permitem inserções e remoções eficientes, além de lidar adequadamente com a variação dinâmica do número de pacientes e atendimentos.

## Complexidade Computacional (Visão Geral)

* Inserção na fila de prioridade: O(n)
* Remoção do próximo paciente: O(1)
* Listagem da fila de espera: O(n)
* Inserção de atendimento no prontuário: O(1)
* Busca no histórico médico: O(n)

## Tecnologias e Linguagem

* Linguagem: C
* Paradigma: Programação estruturada
* Gerenciamento de memória: alocação dinâmica

## Participantes

* Milena Oliveira Penhalves
* Giovana Fernandes Porto
* Giovanna Borges Basso

## Considerações Finais

Este projeto visa consolidar a base conceitual da disciplina de Algoritmos e Estruturas de Dados I, demonstrando a aplicação prática de listas encadeadas em um problema realista, com foco em clareza, organização e eficiência algorítmica.

---

### Executar projeto

```bash
clang -std=c11 -Wall -Wextra -Wpedantic -O2 -o bin/app main.c triagem_fila/*.c prontuario/*.c utils/*.c

./bin/app
```