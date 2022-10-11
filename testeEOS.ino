 // Preparação do Arduino, este código irá rodar uma única vez
#include "tarefa.h"
#include "escalonador.h"

//Assinatura das tarefas
void imprimir();
void imprimir2();
void imprimir3();
void piscar();

//handle das tarefas 
Tarefa t0;
Tarefa t1;
Tarefa t2;
Tarefa t3;

void setup() 
{
  // Colocamos o pino 13 do Arduino como OUTPUT (saída)
 pinMode(13, OUTPUT);
 Serial.begin(9600);

 //Criação das tarefas
 //add_tarefa(codigo, "nome_da_funcao", periodo, prioridade, &endereco_da_tarefa);
 add_tarefa(imprimir, "imprimir", 100, 1, &t0);
 add_tarefa(imprimir2, "imprimir2", 200, 1, &t1);
 add_tarefa(imprimir3, "imprimir3", 400, 1, &t2);
 add_tarefa(piscar, "piscar", 50, 1, &t3);

//funções do SO
 setupEOS2560();
 executar();
 
 }

void loop() {
    // Este código irá se repetir eternamente
}

//Rotinas das tarefas
void piscar(){
   while(true){
  // Ativamos o pino 13 (colocando 5v nele)  
  digitalWrite(13, HIGH);
  
  // Aguardamos 1 segundo
  delay(1000);

  // Desligamos o pino 13
  digitalWrite(13, LOW);

  // Aguardamos mais um segundo
  delay(1000);
  //Serial.println("tarefa 0");
   }
}


void imprimir(){
  //while(true){
    Serial.println("tarefa1"); 
    //delay(1000);
 // } 
}

void imprimir2(){
 while(true){
    Serial.println("tarefa2");
    delay(1000);
 }  
}

void imprimir3(){
 //while(true){
   Serial.println("tarefa3");
   //delay(1000);
 //}  
}
