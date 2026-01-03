//
// Created by leona on 16/12/2025.
//

#include "menus.h"
#include <stdio.h>

#include "../../Outros/Extra/extra.h"
#include "../../Outros/Verificações/verificacoes.h"
#include "../../data/enumeracoes.h"

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




