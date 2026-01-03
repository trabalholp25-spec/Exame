/**
* @file menus_ordens.cpp
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém o menu para a movimentação no tópico das ordens.
 */


#include "menu_ordens.h"
#include <stdio.h>
#include "../../data/structs.h"

// --- Menu de Estado da Ordem ---
// Permite ao utilizador selecionar o estado atual da ordem
EstadoManutencao MenuEstadoOrdens() {
    int opcao;
    do {
        printf("\n----- Menu de Estado -----\n");
        printf("0 - Iniciar\n");      // Ordem ainda não começou
        printf("1 - A Decorrer\n");   // Ordem em andamento
        printf("2 - Concluido\n");    // Ordem finalizada
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2); // validação da escolha

    return (EstadoManutencao)opcao; // converte para enum EstadoManutencao
}

// Converte enum EstadoManutencao em string para exibição
const char* EstadoManutencaoToStr(EstadoManutencao e) {
    switch (e) {
        case Iniciado: return "Iniciado";
        case Decorrer: return "A Decorrer";
        case Concluido: return "Concluido";
        default: return "Desconhecida"; // valor inválido ou desconhecido
    }
}

// --- Menu de Prioridade da Ordem ---
// Permite escolher a prioridade da ordem (Baixa, Normal ou Alta)
PrioridadeManutencao MenuPrioridadeOrdens() {
    int opcao;
    do {
        printf("\n----- Menu de Prioridade -----\n");
        printf("0 - Baixa\n");
        printf("1 - Normal\n");
        printf("2 - Alta\n");
        printf("Escolha a prioridade: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2); // validação do input

    return (PrioridadeManutencao)opcao; // retorna enum PrioridadeManutencao
}

// Converte enum PrioridadeManutencao em string para exibição
const char* PrioridadeManutencaoToStr(PrioridadeManutencao e) {
    switch (e) {
        case Baixa: return "Baixa";
        case Normal: return "Normal";
        case Alta: return "Alta";
        default: return "Desconhecida"; // valor inválido
    }
}

// --- Menu de Gestão de Técnicos / Ordens ---
// Menu principal para gerir ordens de manutenção e trabalhos
int MenuGestao() {
    int opcao;
    do {
        printf("\n----- Menu de Gestão -----\n");
        printf("1 - Listar Ordens de Manutenção\n");  // Ver ordens existentes
        printf("2 - Começar trabalho\n");             // Iniciar uma ordem
        printf("3 - Finalizar Ordem de Trabalho\n");  // Encerrar uma ordem
        printf("Escolha a opção: ");
        scanf("%d", &opcao);
    } while (opcao < 1 || opcao > 3); // valida input

    return opcao;
}

// --- Menu de Tipo de Ordem ---
// Permite escolher se a ordem é preventiva ou corretiva
TipoManutencao MenuTipoOrdens() {
    int opcao;
    do {
        printf("\n----- Tipo de Ordem de Manutenção -----\n");
        printf("0 - Preventiva\n");  // Manutenção programada
        printf("1 - Corretiva\n");   // Manutenção devido a falha
        printf("Escolha o tipo: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 1); // valida input

    return (TipoManutencao)opcao; // retorna enum TipoManutencao
}

// Converte enum TipoManutencao em string para exibição
const char* TipoManutencaoToStr(TipoManutencao e) {
    switch (e) {
        case PREVENTIVA: return "Preventiva";
        case CORRETIVA: return "Corretiva";
        default: return "Desconhecida"; // valor inválido
    }
}
