#ifndef ESCALONADOR_H
#define ESCALONADOR_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif

#include "tarefa.h"

void iniciar_escalonador(Tarefa *proc[], int NUM_TAREFAS);

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif

#endif
