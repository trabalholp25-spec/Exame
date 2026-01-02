//
// Created by leona on 23/12/2025.
//

#include "menu_ordens.h"
#include <stdio.h>
#include "../../data/structs.h"

// Menu do Estado da Ordens

EstadoManutencao MenuEstadoOrdens() {
    int opcao;
    do {
        printf("\n----- Menu de Estado -----\n");
        printf("0 - Iniciar\n");
        printf("1 - A Decorrer\n");
        printf("2 - Concluido\n");
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2);

    return (EstadoManutencao)opcao;
}

const char* EstadoManutencaoToStr(EstadoManutencao e) {
    switch (e) {
        case Iniciado: return "Iniciado";
        case Decorrer:    return "A Decorrer";
        case Concluido:   return "Concluido";
        default:         return "Desconhecida";
    }
}

PrioridadeManutencao MenuPrioridadeOrdens() {
    int opcao;
    do {
        printf("\n----- Menu de Prioridade -----\n");
        printf("0 - Baixa\n");
        printf("1 - Normal\n");
        printf("2 - Alta\n");
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2);

    return (PrioridadeManutencao)opcao;
}

const char* PrioridadeManutencaoToStr(PrioridadeManutencao e) {
    switch (e) {
        case Baixa: return "Baixa";
        case Normal:    return "Normal";
        case Alta:   return "Alta";
        default:         return "Desconhecida";
    }
}

// Menu para gerir na parte dos tecnicos

int MenuGestao() {
    int opcao;
    do {
        printf("\n----- Menu de Gestão -----\n");
        printf("1 - Listar Ordens de Manutenção\n");
        printf("2 - Começar trabalho\n");
        printf("3 - Finalizar Ordem de Trabalho\n");
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 3);

    return opcao;
}

// Menu Tipo da Ordem

TipoManutencao MenuTipoOrdens() {
    int opcao;
    do {
        printf("\n----- Tipo de Ordem de Manutenção -----\n");
        printf("0 - Preventiva\n");
        printf("1 - Corretiva\n");
        printf("Escolha o tipo: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 1);

    return (TipoManutencao)opcao;
}

const char* TipoManutencaoToStr(TipoManutencao e) {
    switch (e) {
        case PREVENTIVA: return "Preventiva";
        case CORRETIVA:    return "Corretiva";
        default:         return "Desconhecida";
    }
}
