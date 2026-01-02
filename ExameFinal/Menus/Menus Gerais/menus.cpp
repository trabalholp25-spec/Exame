//
// Created by leona on 16/12/2025.
//

#include "menus.h"
#include <stdio.h>

#include "../../extra.h"
#include "../../verificacoes.h"
#include "../../data/enumeracoes.h"

int Menu1() {
    int a, escolha = 0;
    do {
        printf ("\n----- Menu Geral -----");
        printf ("\n1 - Ativos");
        printf ("\n2 - Departamentos");
        printf ("\n3 - Ordem de Manutenção");
        printf ("\n4 - Técnicos");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d", &a);

    } while (a < 0 || a > 4);

    return a;
}





