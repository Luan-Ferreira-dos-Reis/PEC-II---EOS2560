#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "tarefa.h"

void iniciar_escalonador(Tarefa *proc[], int NUM_TAREFAS){
  while(true){
    for (int i = 0; i < NUM_TAREFAS; i++){
      proc[i]->codigo();
    }
  }
  
}






#endif
