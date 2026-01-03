/**
* @file menus_tecnicos.h
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declaração de todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém o menu para a movimentação no tópico dos técnicos.
 */
#ifndef EXAMEFINAL_MENUS_TECNICOS_H
#define EXAMEFINAL_MENUS_TECNICOS_H
#include "../../data/structs.h"

Especialidade MenuEspecialidade();
const char* EspecialidadeToStr(Especialidade e);
EstadoTecnico MenuEstado();
const char* EstadoTecnicoToStr(EstadoTecnico e);
int MenuTecnicos();

#endif //EXAMEFINAL_MENUS_TECNICOS_H