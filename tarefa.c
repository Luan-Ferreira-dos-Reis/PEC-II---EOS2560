#include "tarefa.h"

// funções relacionadas a tarefas

void criarTarefa( ptrFunc Xcodigo, char const *Xnome, int Xperiodo, int Xprioridade, Tarefa *novaTarefa){
  novaTarefa->nome = Xnome;
  novaTarefa->codigo = Xcodigo;
  novaTarefa->periodo = Xperiodo;
  novaTarefa->prioridade = Xprioridade;
}
