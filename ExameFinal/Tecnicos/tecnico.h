/**
* @file tecnico.h
 * @author Grupo 37
 * @date 23-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declarações de funções para criar e eliminar técnicos.
 *
 * Este ficheiro contém as declarações das funções utilizadas para gerir técnicos,
 * incluindo criação de um novo técnico e marcação de técnicos como inativos(eliminar tecnicos).
 */
#ifndef EXAMEFINAL_TECNICO_H
#define EXAMEFINAL_TECNICO_H
#include "../data/structs.h"

Tecnico CriarTecnico();
void EliminarTecnico();
void AtivarTecnico();
int AtualizarEstadoTecnico(int idTecnico, EstadoTecnico novoEstado);

#endif //EXAMEFINAL_TECNICO_H