/**
* @file leitura_departamentos.h
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declaração das funções gerais do tópico da listagem de departamentos.
 *
 * Este ficheiro contém a declaração das funções utilizadas para listar Departamentos com/sem filtros.
 */

#ifndef EXAMEFINAL_LEITURA_DEPARTAMENTOS_H
#define EXAMEFINAL_LEITURA_DEPARTAMENTOS_H

void ListarDepartamentos();
void ListarDepartamentosDesativados();
int compararOrdens(const void *a, const void *b);
void OrdenarDepartamentosPorOrdens();
int DepartamentosExistentes();


#endif //EXAMEFINAL_LEITURA_DEPARTAMENTOS_H