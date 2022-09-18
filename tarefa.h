#ifndef TAREFA_H
#define TAREFA_H

#include<Arduino.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif

// ponteiro da função
typedef void(*ptrFunc)(); 

// estrutura para criação de tarefas
typedef struct{
  char const *nome;                 // nome da tarefa
  ptrFunc codigo;             // código da tarefa
  int periodo;                // periodo disponível de execução 
  int prioridade;              // nível de prioridade(quanto menor mais prioritário)
}Tarefa;

// assinatura de funções
void criarTarefa( ptrFunc Xcodigo, char const *Xnome, int Xperiodo, int Xprioridade, Tarefa *novaTarefa);


/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif

#endif

/*
 * 
 * 
 */
