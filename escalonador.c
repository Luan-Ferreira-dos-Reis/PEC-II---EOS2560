#include "escalonador.h"
#include "tarefa.h"

#include <Arduino.h>
#include <stdio.h>

#define TEMPO_INTERRUPCAO 65500

int tarefa_exec; // tarefa em execução

// rotinas do escalonador

void configuraTimer(){
   // Configuração do timer1 
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = TEMPO_INTERRUPCAO;                    // incia timer com valor para que estouro ocorra em 1 segundo
                                     // 65536-(16MHz/1024/1Hz) = 49911 = 
  
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
}


void iniciar_escalonador(Tarefa *proc[], int NUM_TAREFAS){
  int i;
  while(true){
    for(i = 0; i<NUM_TAREFAS; i++){
      proc[i]->codigo();
    }
  }
}

/*
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
  TCNT1 = 65500;                                 // Renicia TIMER
  Serial.println("interrupção");
}
*/
