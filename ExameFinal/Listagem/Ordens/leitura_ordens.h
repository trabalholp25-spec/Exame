/**
* @file leitura_ordens.h
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declaração das funções gerais do tópico da listagem de ordens.
 *
 * Este ficheiro contém a declaração das funções utilizadas para listar todas as ordens com/sem filtros.
 */

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