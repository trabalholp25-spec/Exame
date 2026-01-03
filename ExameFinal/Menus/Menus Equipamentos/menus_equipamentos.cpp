//
// Created by leona on 23/12/2025.
//

#include <stdio.h>
#include "../../data/structs.h"

// Menu Categoria Equipamento
CategoriaAtivo MenuCategoria() {
    int opcao;
    do {
        printf("\n Categoria do Equipamento:");
        printf("\n 1 - Viatura");
        printf("\n 2 - Equipamento Informático");
        printf("\n 3 - Mobiliário Urbano");
        printf("\n 4 - Ferramenta");
        printf("\n 5 - Outra");
        printf("\n Escolha:");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 5);

    return (CategoriaAtivo)opcao;
}

const char* CategoriaToStr(CategoriaAtivo e) {
    switch (e) {
        case VIATURA: return "Viatura";
        case EQUIPAMENTO_INFORMATICO:    return "Equipamento Informático";
        case MOBILIARIO_URBANO: return "Mobiliário Urbano";
        case FERRAMENTA:    return "Ferramenta";
        case OUTRA:       return "Outra";
        default:          return "Desconhecida";
    }
}

// Menu Estado Equipamento

EstadoEquipamento MenuEstadoAtivos() {
    int opcao;
    do {
        printf("\n----- Menu de Estado -----\n");
        printf("0 - Disponível\n");
        printf("1 - Em Operação\n");
        printf("2 - Em Reparação\n");
        printf("3 - Abatido\n");
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 3);

    return (EstadoEquipamento)opcao;
}

const char* EstadoAtivoToStr(EstadoEquipamento e) {
    switch (e) {
        case Operacional: return "Disponível";
        case EmOperacao:    return "Em Operação";
        case EmReparacao:   return "Em Reparacao";
        case Abatido:     return "Abatido";
        case Inativo:    return "Inativo";   // <-- faltava este caso
        default:         return "Desconhecida";
    }
}

// Menu Principal Ativos
int MenuAtivos() {
    int a;
    do {
        printf ("\n----- Menu Geral -----");
        printf ("\n1 - Criar Ativo");
        printf ("\n2 - Listar Ativos");
        printf ("\n3 - Eliminar Ativo");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d", &a);

    } while (a < 0 || a > 3);

    return a;
}

// Menu Listar Ativos
int MenuListarAtivos() {
    int a;

    do {
        printf ("\n----- Menu Listar Ativos -----");
        printf ("\n1 - Listar por categoria");
        printf ("\n2 - Listar por Estado");
        printf ("\n3 - Listar Geral");
        printf ("\n0 - Voltar");
        printf ("\nEscolha:");
        scanf ("%d", &a);
    }while (a < 0 || a > 3);

    return a;
}

// Menu Mudar Estado Equipamentos
EstadoEquipamento MenuMudarEstadoAtivos() {
    int opcao;
    do {
        printf("\n----- Menu de Mudar Estado -----\n");
        printf("0 - Disponível\n");
        printf("1 - Em Reparação\n");
        printf("2 - Abatido\n");
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2);

    return (EstadoEquipamento)opcao;
}