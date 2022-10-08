#include "escalonador.h"
#include "tarefa.h"

//bibliotecas
#include <Arduino.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif

//constantes do sistema
#define TEMPO_INTERRUPCAO 49911
#define SIM 1
#define NAO 0

//variáveis globais
int tarefa_exec = 0;  // tarefa em execução
Tarefa **processos;    // buffer de tarefas
int quantTarefas = 0; //quantidade de tarefas
int *prazoTarefas;  //deadlines para execução de cada tarefa

//configuração do timer do sistema
void configuraTimer(){
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = TEMPO_INTERRUPCAO;         // incia timer com valor para que estouro ocorra em 1 segundo
                                    
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
}

//adicionar tarefa no sistemas
void add_tarefa( ptrFunc _codigo, char const *_nome, int _periodo, int _prioridade,Tarefa *novaTarefa){
  novaTarefa->nome = _nome;
  novaTarefa->codigo = _codigo;
  novaTarefa->periodo = _periodo;
  novaTarefa->prioridade = _prioridade;
  novaTarefa->execucao = NAO;

  //alocando processo no buffer de processos
  processos = (Tarefa**) realloc(processos,sizeof(Tarefa));
  processos[quantTarefas] = novaTarefa;

  //alocando vetor com deadline das tarefas
  prazoTarefas = (int*) realloc(prazoTarefas,sizeof(int));
  prazoTarefas[quantTarefas] = processos[quantTarefas]->periodo;
  
  quantTarefas++;
}

//execução do código das tarefas e troca de contexto
void executar(){
  while(true){   
    if(processos[tarefa_exec]->execucao == SIM){
      processos[tarefa_exec]->codigo();
      prazoTarefas[tarefa_exec] = processos[tarefa_exec]->periodo;
    } 
    tarefa_exec++;
    if(tarefa_exec >= quantTarefas){
      tarefa_exec = 0;
    }
  }
}

//calculo do tempo para execução de cada tarefa
int calcTempoExec(int periodo){
  return 65536 - (15625/(1000/periodo)); //  65536-(16MHz/1024/frequencia)
}

void relogio(){
  for(int i = 0; i < quantTarefas; i++){
    prazoTarefas[i]--;
    if(prazoTarefas[i] == 0){
       processos[i]->execucao = SIM;
    }
  }
}


//função de interrupção ativada por timer que incrementa o buffer de tarefas
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
  relogio();
  TCNT1 = 65530;
}

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
