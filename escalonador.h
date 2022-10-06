#ifndef ESCALONADOR_H
#define ESCALONADOR_H



/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif


//inclusão de bibliotecas
#include "tarefa.h"
#include <Arduino.h>

//assinatura de funções
void configuraTimer();
void iniciar(Tarefa *proc[], int NUM_TAREFAS);
int calcTempoExec(int periodo);
void executar();

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif

#endif
