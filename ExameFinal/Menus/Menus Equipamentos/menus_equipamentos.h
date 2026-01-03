/**
* @file menus_equipamentos.h
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém os menus para a movimentação dentro do tópico da equipamentos/ativos.
 */


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