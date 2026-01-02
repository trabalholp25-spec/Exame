//
// Created by leona on 23/12/2025.
//

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
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3);

    return a;
}