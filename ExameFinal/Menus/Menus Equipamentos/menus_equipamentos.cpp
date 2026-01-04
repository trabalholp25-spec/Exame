/**
* @file menus_equipamentos.cpp
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

#include <stdio.h>
#include "../../data/structs.h"

// --- Menu de Categoria do Equipamento ---
// Permite ao utilizador escolher a categoria de um ativo
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
    } while (opcao < 0 || opcao > 5); // valida que a escolha é válida

    return (CategoriaAtivo)opcao; // retorna a escolha como enum CategoriaAtivo
}

// Converte enum CategoriaAtivo em string para exibição
const char* CategoriaToStr(CategoriaAtivo e) {
    switch (e) {
        case VIATURA: return "Viatura";
        case EQUIPAMENTO_INFORMATICO: return "Equipamento Informático";
        case MOBILIARIO_URBANO: return "Mobiliário Urbano";
        case FERRAMENTA: return "Ferramenta";
        case OUTRA: return "Outra";
        default: return "Desconhecida"; // caso inesperado
    }
}

// --- Menu de Estado do Equipamento ---
// Permite selecionar o estado atual do ativo
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
    } while (opcao < 0 || opcao > 3); // valida input

    return (EstadoEquipamento)opcao; // retorna como enum EstadoEquipamento
}

// Converte enum EstadoEquipamento em string para exibição
const char* EstadoAtivoToStr(EstadoEquipamento e) {
    switch (e) {
        case Operacional: return "Disponível";
        case EmOperacao: return "Em Operação";
        case EmReparacao: return "Em Reparacao";
        case Abatido: return "Abatido";
        case Inativo: return "Inativo"; // caso que faltava no teu código original
        default: return "Desconhecida"; // qualquer valor inválido
    }
}

// --- Menu Principal de Gestão de Ativos ---
// Menu geral para criar, listar ou eliminar ativos
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

    } while (a < 0 || a > 3); // valida input

    return a;
}

// --- Menu de Listagem de Ativos ---
// Escolhas para listar ativos de formas diferentes
int MenuListarAtivos() {
    int a;
    do {
        printf ("\n----- Menu Listar Ativos -----");
        printf ("\n1 - Listar por categoria"); // filtra por categoria
        printf ("\n2 - Listar por Estado");    // filtra por estado
        printf ("\n3 - Listar Geral");         // lista todos
        printf ("\n0 - Voltar");               // retorna ao menu anterior
        printf ("\nEscolha:");
        scanf ("%d", &a);
    } while (a < 0 || a > 3);

    return a;
}

// --- Menu de Mudança de Estado de Ativos ---
// Menu específico para alterar o estado de um ativo existente
EstadoEquipamento MenuMudarEstadoAtivos() {
    int opcao;
    do {
        printf("\n----- Menu de Mudar Estado -----\n");
        printf("0 - Disponível\n");
        printf("1 - Em Reparação\n");
        printf("2 - Abatido\n");
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2); // valida input

    return (EstadoEquipamento)opcao; // retorna a escolha como enum
}