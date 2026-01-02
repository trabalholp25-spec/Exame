//
// Created by leona on 23/12/2025.
//

#ifndef EXAMEFINAL_MENUS_EQUIPAMENTOS_H
#define EXAMEFINAL_MENUS_EQUIPAMENTOS_H
#include "../../data/structs.h"

// Ativos(Equipamentos)
CategoriaAtivo MenuCategoria();
const char* CategoriaToStr(CategoriaAtivo e);
// Estado Equipamentos
EstadoEquipamento MenuEstadoAtivos();
const char* EstadoAtivoToStr(EstadoEquipamento e);

// Menu Principal Ativos
int MenuAtivos();

// Menu Listar Ativos
int MenuListarAtivos();

#endif //EXAMEFINAL_MENUS_EQUIPAMENTOS_H