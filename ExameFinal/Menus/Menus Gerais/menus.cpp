/**
* @file menus.cpp
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém o menu para a movimentação Inicial.
 */

#include "menus.h"
#include <stdio.h>

// Menu Geral
int Menu1() {
    int a ;

        printf ("\n----- Menu Geral -----");
        printf ("\n1 - Ativos");
        printf ("\n2 - Departamentos");
        printf ("\n3 - Ordem de Manutenção");
        printf ("\n4 - Técnicos");
        printf ("\n5 - Relatórios");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d", &a);

    return a;
}




