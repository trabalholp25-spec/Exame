/**
* @file menus_administracao.cpp
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém os menus para a movimentação dentro do tópico da administração.
 */

#include <stdio.h>
#include "menus_administracao.h"

// --- Menu principal de Administração ---
// Permite ao utilizador escolher o tipo de relatório geral
int MenuAdministracao() {
    int a;
    do {
        printf ("\n----- Menu Geral De Administração -----");
        printf ("\n1 - Relatórios sobre Ativos");       // Leva ao menu de ativos
        printf ("\n2 - Relatórios sobre Departamentos"); // Leva ao menu de departamentos
        printf ("\n3 - Relatórios sobre Ordens");        // Leva ao menu de ordens
        printf ("\n4 - Relatórios sobre Técnicos");     // Leva ao menu de técnicos
        printf ("\n0 - Sair");                          // Sai do menu
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 4); // Valida input (0 a 4)

    return a; // Retorna a escolha do utilizador
}

// --- Menu de Relatórios de Ativos ---
// Permite operações específicas sobre ativos
int MenuRelatoriosAtivos() {
    int a;
    do {
        printf ("\n----- Menu Administração de Ativos -----");
        printf ("\n1 - Total de Ativos Existentes"); // Mostra contagem total
        printf ("\n2 - Listagem de Ativos Filtrados"); // Permite filtragem por categoria/estado
        printf ("\n3 - Ranking de Ativos"); // Classifica ativos por algum critério
        printf ("\n0 - Sair"); // Retorna ao menu anterior
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3); // Valida input

    return a;
}

// --- Menu de Listagem de Ativos ---
// Escolhas para listar ativos filtrados
int MenuListagemAtivos() {
    int a;
    do {
        printf ("\n----- Menu Listagem de Ativos -----");
        printf ("\n1 - Listar Ativos por Categoria");
        printf ("\n2 - Listar Ativos por Estado");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 2);

    return a;
}

// --- Menu de Relatórios de Departamentos ---
int MenuRelatoriosDept() {
    int a;
    do {
        printf ("\n----- Menu Administração de Departamentos -----");
        printf ("\n1 - Total de Departamentos Existentes");
        printf ("\n2 - Listagem de Relatórios Filtrados");
        printf ("\n3 - Ranking de Departamentos");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3);

    return a;
}

// --- Menu de Relatórios de Ordens de Manutenção ---
int MenuRelatoriosOrdens() {
    int a;
    do {
        printf ("\n----- Menu Administração de Ordens de Manutenção -----");
        printf ("\n1 - Listar Ordens de Manutenção"); // Mostra todas as ordens
        printf ("\n2 - Cálculo do Tempo médio de resolução"); // Estatística de tempo
        printf ("\n3 - Análise de custos"); // Estatística de custos
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3);

    return a;
}

// --- Menu de Listagem de Ordens ---
int MenuListagemOrdens() {
    int a;
    do {
        printf ("\n----- Menu Listagem de Ordens de Manutenção -----");
        printf ("\n1 - Listar Ordens por Estado");
        printf ("\n2 - Listar Ordens por Categoria");
        printf ("\n3 - Listar Ordens por Prioridade");
        printf ("\n4 - Listar Ordens Concluidas");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 4);

    return a;
}

// --- Menu de Relatórios de Técnicos ---
int MenuRelatoriosTecnicos() {
    int a;
    do {
        printf ("\n----- Menu Administração de Técnicos -----");
        printf ("\n1 - Listar os Técnicos"); // Mostra todos os técnicos
        printf ("\n2 - Taxa de Ocupação"); // Mostra percentagem de ocupação
        printf ("\n3 - Ranking dos Técnicos"); // Classifica técnicos por desempenho
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3);

    return a;
}

// --- Menu de Listagem de Técnicos ---
int MenuListagemTecnicos() {
    int a;
    do {
        printf ("\n----- Menu Listagem de Tecnicos -----");
        printf ("\n1 - Listar Técnicos por Especialidade"); // Filtra por área
        printf ("\n2 - Listar Técnicos por Disponibilidade"); // Filtra por estado
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 2);

    return a;
}