/**
* @file menus_tecnicos.cpp
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de menus deste tópico.
 *
 * Este ficheiro contém o menu para a movimentação no tópico dos técnicos.
 */


#include "menus_tecnicos.h"
#include <stdio.h>
#include "../../data/structs.h"

// --- Menu de Especialidade do Técnico ---
// Permite escolher a especialidade do técnico a criar ou editar
Especialidade MenuEspecialidade() {
    int opcao;
    do {
        printf("\n----- Menu de Especialidades -----\n");
        printf("0 - Eletricista\n");   // Técnico especializado em eletricidade
        printf("1 - Mecânico\n");       // Técnico especializado em mecânica
        printf("2 - Informático\n");    // Técnico especializado em informática
        printf("3 - Pedreiro\n");       // Técnico especializado em alvenaria/construção
        printf("4 - Pintor\n");         // Técnico especializado em pintura
        printf("5 - Outro\n");          // Qualquer outra especialidade
        printf("Escolha a especialidade: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 5); // validação da opção

    return (Especialidade)opcao; // converte input para enum Especialidade
}

// Converte enum Especialidade em string para exibição
const char* EspecialidadeToStr(Especialidade e) {
    switch (e) {
        case ELETRICISTA: return "Eletricista";
        case MECANICO:    return "Mecânico";
        case INFORMATICO: return "Informático";
        case PEDREIRO:    return "Pedreiro";
        case PINTOR:      return "Pintor";
        case OUTRO:       return "Outro";
        default:          return "Desconhecida"; // valor inválido
    }
}

// --- Menu de Estado do Técnico ---
// Permite escolher o estado atual do técnico
EstadoTecnico MenuEstado() {
    int opcao;
    do {
        printf("\n----- Menu de Estado -----\n");
        printf("0 - Disponível\n"); // Técnico disponível para ordens
        printf("1 - Ocupado\n");     // Técnico atualmente em trabalho
        printf("2 - Férias\n");      // Técnico de férias
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2); // validação do input

    return (EstadoTecnico)opcao; // converte input para enum EstadoTecnico
}

// Converte enum EstadoTecnico em string para exibição
const char* EstadoTecnicoToStr(EstadoTecnico e) {
    switch (e) {
        case DISPONIVEL: return "Disponível";
        case OCUPADO:    return "Ocupado";
        case FERIAS:     return "Férias";
        case INATIVO:    return "Inativo";   // estado adicional para técnicos desativados
        default:         return "Desconhecida";
    }
}

// --- Menu Principal de Técnicos ---
// Menu de gestão geral para criar, listar, eliminar ou gerir técnicos
int MenuTecnicos() {
    int a;
    do {
        printf ("\n----- Menu Geral -----");
        printf ("\n1 - Criar Técnico");                 // Inserir novo técnico no sistema
        printf ("\n2 - Listar Técnico");                // Mostrar lista de técnicos
        printf ("\n3 - Eliminar Técnico");              // Desativar ou remover técnico
        printf ("\n4 - Gerir Ordens de Manutenção");    // Associar ou gerir técnicos em ordens
        printf ("\n5 - Ativar Técnico");                // Reativar técnico previamente eliminado
        printf ("\n0 - Sair");                          // Sair do menu
        printf ("\nEscolha:");
        scanf ("%d", &a);
    } while (a < 0 || a > 5); // valida input

    return a; // retorna a opção selecionada
}