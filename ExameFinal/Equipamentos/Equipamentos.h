/**
* @file Equipamentos.h
 * @author Grupo 37
 * @date 31-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico "ativos"/"equipamentos"
 *
 * Este ficheiro contém as declarações das funções utilizadas para gerir todo o tipo de criação/eliminação e gestão de ativos.
 * Além disso gere a quantidade de reparos de cada Ativo.
 */
#ifndef EXAMEFINAL_EQUIPAMENTOS_H
#define EXAMEFINAL_EQUIPAMENTOS_H
#include "../data/structs.h"

Ativo CriarEquipamento();
void EliminarAtivos();
int AtualizarEstadoAtivo(int idAtivo, EstadoEquipamento novoEstado);
void AdicionarReparo(int Id);

#endif //EXAMEFINAL_EQUIPAMENTOS_H