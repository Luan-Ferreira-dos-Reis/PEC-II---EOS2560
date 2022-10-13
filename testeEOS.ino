// Preparação do Arduino, este código irá rodar uma única vez
#include "tarefa.h"
#include "escalonador.h"

#include <math.h>

#define AOUT        9

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

Tarefa sineTaskH;

void setup() 
{
  // Colocamos o pino 13 do Arduino como OUTPUT (saída)
 pinMode(13, OUTPUT);
 Serial.begin(9600);

 //Criação das tarefas
 //add_tarefa(codigo, "nome_da_funcao", periodo, prioridade, &endereco_da_tarefa);
 //add_tarefa(imprimir, "imprimir", 50, 1, &t0);
 //add_tarefa(imprimir2, "imprimir2", 100, 1, &t1);
 //add_tarefa(imprimir3, "imprimir3", 200, 1, &t2);
 add_tarefa(piscar, "piscar", 50, 1, &t3);

 add_tarefa(SineTask, "SineTask",20,1, &sineTaskH);
                

//funções do SO
 setupEOS2560();
 executar();
 }

void loop() {
    // Nada executa aqui.
}

//Rotinas das tarefas
void piscar(){  
  // Ativamos o pino 13 (colocando 5v nele)  
  Serial.println("piscar LED HIGH");
  digitalWrite(13, HIGH);
  
  // Aguardamos 1 segundo
  delay(100);

  // Desligamos o pino 13
  digitalWrite(13, LOW);
  

  // Aguardamos mais um segundo
  delay(100);
  Serial.println("piscar LED LOW"); 
}


void imprimir(){
    Serial.println("tarefa1 inicio"); 
    delay(100);
    Serial.println("tarefa1 meio");
    delay(100);
    Serial.println("tarefa1 fim"); 
}

void imprimir2(){

    Serial.println("tarefa2 inicio"); 
    delay(1000);
    Serial.println("tarefa2 meio");
    delay(1000);
    Serial.println("tarefa2 fim"); 
}

void imprimir3(){

    Serial.println("tarefa3 inicio"); 
    delay(1000);
    Serial.println("tarefa3 meio");
    delay(1000);
    Serial.println("tarefa3 fim"); 
}

void SineTask() {
    Serial.println("seno in");
    unsigned int stime=0, etime=0;
    pinMode(AOUT, OUTPUT);
    unsigned int outpv = 0;
    unsigned int period = 0;
    //while(1) {
        stime = millis();
        for(period = 0; period < 16; ++period){
            etime = millis();
            outpv = (unsigned int)((sin(2*PI*2*(etime - stime)*0.001)+1)*127.5);  /*Senoide = seno(2*PI*Freq*t)*/
            analogWrite(AOUT, outpv);
            delay(33);
        }
   // }
   Serial.println("seno out");
}
