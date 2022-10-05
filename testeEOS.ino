 // Preparação do Arduino, este código irá rodar uma única vez
#include "tarefa.h"
#include "escalonador.h"

#define NUM_TAREFAS 3

//Assinatura das tarefas
void piscar();
void imprimir();
void imprimir2();
void imprimir3();
 
Tarefa t0;
Tarefa t1;
Tarefa t2;
Tarefa *proc[NUM_TAREFAS];


void setup() 
{
  // Colocamos o pino 13 do Arduino como OUTPUT (saída)
 pinMode(13, OUTPUT);
 Serial.begin(9600);
 configuraTimer();


 //Criação das tarefas
 //criarTarefa(piscar, "piscar", 20, 1, &t0);
 criarTarefa(imprimir3, "imprimir3", 20, 1, &t0);
 criarTarefa(imprimir, "imprimir", 20, 1, &t1);
 criarTarefa(imprimir2, "imprimir2", 20, 1, &t2);
 
 proc[0] = &t0;
 proc[1] = &t1;
 proc[2] = &t2;

 //configura timer do SO
 //configuraTimer();
 iniciar_escalonador(proc, NUM_TAREFAS);
 
 }

void loop() {
    // Este código irá se repetir eternamente
}

//Rotinas das tarefas

void piscar(){
  // Ativamos o pino 12 (colocando 5v nele)  
  digitalWrite(13, HIGH);
  
  // Aguardamos 1 segundo
  delay(1000);

  // Desligamos o pino 12
  digitalWrite(13, LOW);

  // Aguardamos mais um segundo
  delay(1000);
  //Serial.println("tarefa 0");
}


void imprimir(){
   Serial.println("tarefa 1");
}

void imprimir2(){
   Serial.println("tarefa 2");
}

void imprimir3(){
   Serial.println("tarefa 3");
}
