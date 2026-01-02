
#include <stdio.h>
#include "menus_administracao.h"

int MenuAdministracao() {
    int a;
    do {
        printf ("\n----- Menu Geral De Administração -----");
        printf ("\n1 - Relatórios sobre Ativos");
        printf ("\n2 - Relatórios sobre Departamentos");
        printf ("\n3 - Relatórios sobre Ordens");
        printf ("\n4 - Relatórios sobre Técnicos");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 4);

    return a;
}

// Menus referentes á administração dos Ativos
int MenuRelatoriosAtivos() {
    int a;
    do {
        printf ("\n----- Menu Administração de Ativos -----");
        printf ("\n1 - Total de Ativos Existentes");
        printf ("\n2 - Listagem de Ativos Filtrados");
        printf ("\n3 - Ranking de Ativos");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3);

    return a;
}

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

// Menus referentes á administração dos Departamentos
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

// Menus referentes á administração das Ordens
int MenuRelatoriosOrdens() {
    int a;
    do {
        printf ("\n----- Menu Administração de Ordens de Manutenção -----");
        printf ("\n1 - Listar Ordens de Manutenção");
        printf ("\n2 - Cálculo do Tempo médio de resolução");
        printf ("\n3 - Análise de custos");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3);

    return a;
}

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

    } while (a < 0 || a > 3);

    return a;
}

// Menus referentes á administração daos Tecnicos
int MenuRelatoriosTecnicos() {
    int a;
    do {
        printf ("\n----- Menu Administração de Técnicos -----");
        printf ("\n1 - Listar os Técnicos");
        printf ("\n2 - Taxa de Ocupação");
        printf ("\n3 - Ranking dos Técnicos");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 3);

    return a;
}
int MenuListagemTecnicos() {
    int a;
    do {
        printf ("\n----- Menu Listagem de Tecnicos -----");
        printf ("\n1 - Listar Técnicos por Especialidade");
        printf ("\n2 - Listar Técnicos por Disponibilidade");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d",&a);

    } while (a < 0 || a > 2);

    return a;
}