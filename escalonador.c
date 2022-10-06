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

//inicialização do sistema
//função que importa o ambiente de execução(nº de tarefas, escopo das tarefas, etc) para facilitar a execução
void iniciar(Tarefa *proc[], int NUM_TAREFAS){
  int i;
  quantTarefas = NUM_TAREFAS;
  for (i = 0; i < NUM_TAREFAS; i++){
    processos[i] = (Tarefa*) malloc(sizeof(Tarefa));
  }
 processos = proc;

  
}

//execução do código das tarefas e troca de contexto
void executar(){
  while(true){
    if(tarefa_exec >= quantTarefas){
      tarefa_exec = 0;
    }
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
  tarefa_exec++;
  TCNT1 = calcTempoExec(processos[tarefa_exec]->periodo); 
}
