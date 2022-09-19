// Preparação do Arduino, este código irá rodar uma única vez
#include "tarefa.h"
#include "escalonador.h"
#include<Arduino.h>

#define NUM_TAREFAS 2

//rotina das tarefas
void piscar();
void imprimir();

//criação das tarefas e buffer de tarefas
Tarefa t1;
Tarefa t2;
Tarefa *proc[NUM_TAREFAS];

void setup() 
{
  // Colocamos o pino 13 do Arduino como OUTPUT (saída)
 pinMode(13, OUTPUT);
 Serial.begin(9600);

 //Criação das tarefas
 criarTarefa(piscar, "piscar", 20, 1, &t1);
 criarTarefa(imprimir, "imprimir", 20, 1, &t2);
 proc[0] = &t1;
 proc[1] = &t2;

 //função que inicia escalonador
 iniciar_escalonador(proc, NUM_TAREFAS);
 }

void loop() {
    // Este código irá se repetir eternamente

}

void piscar(){
  // Ativamos o pino 12 (colocando 5v nele)  
  digitalWrite(13, HIGH);
  
  // Aguardamos 1 segundo
  delay(100);

  // Desligamos o pino 12
  digitalWrite(13, LOW);

  // Aguardamos mais um segundo
  delay(100);
}


void imprimir(){
   Serial.println("impressão na serial");
}
