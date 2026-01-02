//
// Created by leona on 23/12/2025.
//

#ifndef EXAMEFINAL_LEITURA_ORDENS_H
#define EXAMEFINAL_LEITURA_ORDENS_H
#include "../../data/structs.h"

EstadoManutencao StrToEstadoOrdem(const char* s);
PrioridadeManutencao StrToPrioridade(const char *s);
void ListarOrdens();
void ListarOrdensIniciandoPorPrioridade();
int CompararPrioridade(const void* a, const void* b);
int ListarOrdensNaoConcluidas();

// Presentes no menu de Administração
void ListarOrdensPorEstado();
void ListarOrdensPorPrioridade();
void ListarOrdensPorTipo();
void ListarOrdensConcluidas();

#endif //EXAMEFINAL_LEITURA_ORDENS_H