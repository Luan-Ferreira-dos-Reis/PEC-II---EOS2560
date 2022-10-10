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
typedef struct {
  char const *nome;                 // nome da tarefa
  ptrFunc codigo;             // código da tarefa
  int periodo;                // periodo disponível de execução 
  int prioridade;              // nível de prioridade(quanto menor mais prioritário)

  int estado;                 //estado do processo BLOQUEADO (0) EXECUCAO(1) ESPERA(2)
  volatile unsigned long pilha;  //pilha da tarefa
}Tarefa;


/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif

#endif

/*
 * 
 * 
 */
