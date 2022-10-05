#include "tarefa.h"

// funções relacionadas a tarefas
void criarTarefa( ptrFunc _codigo, char const *_nome, int _periodo, int _prioridade,Tarefa *novaTarefa){
  novaTarefa->nome = _nome;
  novaTarefa->codigo = _codigo;
  novaTarefa->periodo = _periodo;
  novaTarefa->prioridade = _prioridade;
  novaTarefa->execucao = false;
}
