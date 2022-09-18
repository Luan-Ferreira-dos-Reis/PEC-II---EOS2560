// Preparação do Arduino, este código irá rodar uma única vez
#include "tarefa.h"
#include<Arduino.h>

//rotina das tarefas
void piscar();

//criação das tarefas
Tarefa t1;

void setup() 
{
  /*t1.nome = "piscar";
  t1.periodo = 20;
  t1.prioridade = 1;
  t1.codigo = piscar;*/
  criarTarefa(piscar, "piscar", 20, 1, &t1);
  // Colocamos o pino 13 do Arduino como OUTPUT (saída)
  pinMode(13, OUTPUT);
 Serial.begin(9600);
 }

void loop() {
    // Este código irá se repetir eternamente
  t1.codigo();


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
