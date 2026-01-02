//
// Created by leona on 23/12/2025.
//

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