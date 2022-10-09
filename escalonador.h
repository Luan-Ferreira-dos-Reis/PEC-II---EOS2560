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
void add_tarefa( ptrFunc _codigo, char const *_nome, int _periodo, int _prioridade,Tarefa *novaTarefa);
void setupEOS2560();
int calcTempoExec(int periodo);
void relogio();
void executar();

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif

#endif
