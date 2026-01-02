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

#endif //EXAMEFINAL_MENU_ORDENS_H