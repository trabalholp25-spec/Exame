/**
* @file menus_ordens.h
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declaração de todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém o menu para a movimentação no tópico das ordens.
 */

#ifndef EXAMEFINAL_MENU_ORDENS_H
#define EXAMEFINAL_MENU_ORDENS_H
#include "../../data/structs.h"

EstadoManutencao MenuEstadoOrdens();
const char* EstadoManutencaoToStr(EstadoManutencao e);

PrioridadeManutencao MenuPrioridadeOrdens();
const char* PrioridadeManutencaoToStr(PrioridadeManutencao e);

int MenuGestao();

// Escolha do tipo de ordem
TipoManutencao MenuTipoOrdens();
const char* TipoManutencaoToStr(TipoManutencao e);

#endif //EXAMEFINAL_MENU_ORDENS_H