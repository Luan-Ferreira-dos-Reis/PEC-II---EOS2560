#include "escalonador.h"
#include "tarefa.h"

// rotinas do escalonador
void iniciar_escalonador(Tarefa *proc[], int NUM_TAREFAS){
  while(1){
    for (int i = 0; i < NUM_TAREFAS; i++){
      proc[i]->codigo();
    }
  }
  
}
