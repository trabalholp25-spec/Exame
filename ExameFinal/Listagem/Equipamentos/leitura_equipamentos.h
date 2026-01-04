/**
* @file leitura_equipamentos.h
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declaração das funções gerais do tópico da listagem de equipamentos/ativos.
 *
 * Este ficheiro contém a declaração das funções utilizadas para listar Equipamentos com/sem filtros.
 */

#include "../../data/structs.h"

#ifndef EXAMEFINAL_LEITURA_EQUIPAMENTOS_H
#define EXAMEFINAL_LEITURA_EQUIPAMENTOS_H

void ListarAtivos();
void ListarAtivosPorEstado();
void ListarAtivosPorCategoria();
CategoriaAtivo StrToCategoria(const char *s);
EstadoEquipamento StrToEstadoAtivo(const char *s);
int AtivosExistentes();
int CompararAtivosPorReparos(const void *a, const void *b);
void ListarAtivosPorReparos();

#endif //EXAMEFINAL_LEITURA_EQUIPAMENTOS_H