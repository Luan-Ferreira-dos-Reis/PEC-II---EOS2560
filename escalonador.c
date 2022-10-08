#include "escalonador.h"
#include "tarefa.h"

//bibliotecas
#include <Arduino.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

//constantes do sistema
#define TEMPO_INTERRUPCAO 49911

//variáveis globais
int tarefa_exec = 0;  // tarefa em execução
Tarefa **processos;    // buffer de tarefas
int quantTarefas = 0; //quantidade de tarefas

//configuração do timer do sistema
void configuraTimer(){
   // Configuração do timer1 
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
  novaTarefa->execucao = false;
  
  processos = (Tarefa**) realloc(processos,sizeof(Tarefa));
  processos[quantTarefas] = novaTarefa;
  quantTarefas++;
}

//execução do código das tarefas e troca de contexto
void executar(){
  while(true){   
    processos[tarefa_exec]->codigo();
  }
}

//calculo do tempo para execução de cada tarefa
int calcTempoExec(int periodo){
  return 65536 - (15625/(1000/periodo)); //  65536-(16MHz/1024/frequencia)
}


//função de interrupção ativada por timer que incrementa o buffer de tarefas
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
  //TCNT1 = TEMPO_INTERRUPCAO;                                 // Reinicia TIMER
  if(tarefa_exec >= quantTarefas){
      tarefa_exec = 0;
    }
  tarefa_exec++;
  TCNT1 = calcTempoExec(processos[tarefa_exec]->periodo); 
}
