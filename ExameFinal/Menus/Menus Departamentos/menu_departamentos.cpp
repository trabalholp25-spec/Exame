/**
* @file menus_departamentos.cpp
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém os menus para a movimentação dentro do tópico dos departamentos.
 */


#include "menu_departamentos.h"
#include <stdio.h>

// Menu Principal Departamentos
int MenuDepartamentos() {
    int a;
    do {
        printf ("\n----- Menu Geral -----");
        printf ("\n1 - Criar Departamentos");
        printf ("\n2 - Listar Departamentos");
        printf ("\n3 - Eliminar Departamento");
        printf ("\n4 - Reativar Departamento");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 4);

    return a;
}