// Preparação do Arduino, este código irá rodar uma única vez
#include "tarefa.h"
#include<Arduino.h>

//rotina das tarefas
void piscar();

//criação das tarefas
Tarefa t1;

void setup() 
{
  t1.nome = "piscar";
  t1.periodo = 20;
  t1.prioridade = 1;
  t1.codigo = piscar;
  // Colocamos o pino 12 do Arduino como OUTPUT (saída)
  pinMode(13, OUTPUT);
 Serial.begin(9600);
 char myString[] = "Essa é a primeira linha";
 }

// Este código é chamado automáticamente pelo Arduino, ficará em
// loop até que seu Arduino seja desligado
void loop() 
{
  t1.codigo();

  // Este código irá se repetir eternamente
}

void piscar(){
  // Ativamos o pino 12 (colocando 5v nele)  
  digitalWrite(13, HIGH);
   Serial.println(t1.nome);
   Serial.println(t1.periodo);
   Serial.println(t1.prioridade );
  // Aguardamos 1 segundo
  delay(100);

  // Desligamos o pino 12
  digitalWrite(13, LOW);

  // Aguardamos mais um segundo
  delay(100);
}
