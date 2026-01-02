//
// Created by leona on 23/12/2025.
//

#include "../../data/structs.h"

#ifndef EXAMEFINAL_LEITURA_EQUIPAMENTOS_H
#define EXAMEFINAL_LEITURA_EQUIPAMENTOS_H

void ListarAtivos();
void ListarAtivosPorEstado();
void ListarAtivosPorCategoria();
CategoriaAtivo StrToCategoria(const char *s);
EstadoEquipamento StrToEstadoAtivo(const char *s);

#endif //EXAMEFINAL_LEITURA_EQUIPAMENTOS_H