#include "escalonador.h"
#include "tarefa.h"

//bibliotecas
#include <Arduino.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif



// Macros para salvar e restaurar o contexto
#define portRESTORE_CONTEXT()\
asm volatile (\
"cli \n\t"\
"out __SP_L__, %A0 \n\t"\
"out __SP_H__, %B0 \n\t"\
"pop r31 \n\t"\
"pop r30 \n\t"\
"pop r29 \n\t"\
"pop r28 \n\t"\
"pop r27 \n\t"\
"pop r26 \n\t"\
"pop r25 \n\t"\
"pop r24 \n\t"\
"pop r23 \n\t"\
"pop r22 \n\t"\
"pop r21 \n\t"\
"pop r20 \n\t"\
"pop r19 \n\t"\
"pop r18 \n\t"\
"pop r17 \n\t"\
"pop r16 \n\t"\
"pop r15 \n\t"\
"pop r14 \n\t"\
"pop r13 \n\t"\
"pop r12 \n\t"\
"pop r11 \n\t"\
"pop r10 \n\t"\
"pop r9 \n\t"\
"pop r8 \n\t"\
"pop r7 \n\t"\
"pop r6 \n\t"\
"pop r5 \n\t"\
"pop r4 \n\t"\
"pop r3 \n\t"\
"pop r2 \n\t"\
"pop r1 \n\t"\
"pop r0 \n\t"\
"sei \n\t"\
"out __SREG__, r0\n\t"\
"pop r0 \n\t": : "r" (pxCurrentTCB));

#define portSAVE_CONTEXT()\
asm volatile (\
"push r0 \n\t"\
"in r0, __SREG__ \n\t"\
"cli \n\t"\
"push r0 \n\t"\
"push r1 \n\t"\
"clr r1 \n\t"\
"push r2 \n\t"\
"push r3 \n\t"\
"push r4 \n\t"\
"push r5 \n\t"\
"push r6 \n\t"\
"push r7 \n\t"\
"push r8 \n\t"\
"push r9 \n\t"\
"push r10 \n\t"\
"push r11 \n\t"\
"push r12 \n\t"\
"push r13 \n\t"\
"push r14 \n\t"\
"push r15 \n\t"\
"push r16 \n\t"\
"push r17 \n\t"\
"push r18 \n\t"\
"push r19 \n\t"\
"push r20 \n\t"\
"push r21 \n\t"\
"push r22 \n\t"\
"push r23 \n\t"\
"push r24 \n\t"\
"push r25 \n\t"\
"push r26 \n\t"\
"push r27 \n\t"\
"push r28 \n\t"\
"push r29 \n\t"\
"push r30 \n\t"\
"push r31 \n\t"\
"in r26, __SP_L__ \n\t"\
"in r27, __SP_H__ \n\t"\
"sts pxCurrentTCB+1, r27 \n\t"\
"sts pxCurrentTCB, r26 \n\t"\
"sei \n\t" ::);

//constantes do sistema
#define TEMPO_INTERRUPCAO 0xFFF0
#define SIM 1
#define NAO 0

//variáveis globais
int tarefa_exec = 0;  // tarefa em execução
Tarefa **processos;    // buffer de tarefas
int quantTarefas = 0; //quantidade de tarefas
int *prazoTarefas;  //deadlines para execução de cada tarefa(em milisegeundos)
volatile unsigned long pxCurrentTCB;




//configuração do timer do sistema
void configuraTimer(){
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = TEMPO_INTERRUPCAO;         // incia timer com valor para que estouro ocorra em 1 milisegundo
                                    
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

void setupEOS2560(){
  configuraTimer();
}

//execução do código das tarefas e troca de contexto
void executar(){
  while(true){   
    if(processos[tarefa_exec]->execucao == SIM){                                //tarefa deve ser executada
      //portRESTORE_CONTEXT();//
      processos[tarefa_exec]->codigo();                                         //execucao da tarefa
      prazoTarefas[tarefa_exec] = processos[tarefa_exec]->periodo;              //reinicia prazo para execução
      processos[tarefa_exec]->execucao = NAO;
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

//relogio do sistema(ou temporizador) a cada interrupção do timer decrementa o prazo restante para execução de tarefas
void relogio(){
  for(int i = 0; i < quantTarefas; i++){
    prazoTarefas[i]--;
    if(prazoTarefas[i] == 0){
       processos[i]->execucao = SIM;
    }
  }
}


//função de interrupção ativada por timer que ativa a função relogio do sistema
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
  //portSAVE_CONTEXT();//
  relogio();
  TCNT1 = TEMPO_INTERRUPCAO; //reinicia timer
}

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
