//
// Created by leona on 23/12/2025.
//

#include "menus_tecnicos.h"
#include <stdio.h>
#include "../../data/structs.h"

Especialidade MenuEspecialidade() {
    int opcao;
    do {
        printf("\n----- Menu de Especialidades -----\n");
        printf("0 - Eletricista\n");
        printf("1 - Mecânico\n");
        printf("2 - Informático\n");
        printf("3 - Pedreiro\n");
        printf("4 - Pintor\n");
        printf("5 - Outro\n");
        printf("Escolha a especialidade: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 5);

    return (Especialidade)opcao;
}

const char* EspecialidadeToStr(Especialidade e) {
    switch (e) {
        case ELETRICISTA: return "Eletricista";
        case MECANICO:    return "Mecânico";
        case INFORMATICO: return "Informático";
        case PEDREIRO:    return "Pedreiro";
        case PINTOR:      return "Pintor";
        case OUTRO:       return "Outro";
        default:          return "Desconhecida";
    }
}

EstadoTecnico MenuEstado() {
    int opcao;
    do {
        printf("\n----- Menu de Estado -----\n");
        printf("0 - Disponível\n");
        printf("1 - Ocupado\n");
        printf("2 - Férias\n");
        printf("Escolha o estado: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 2);

    return (EstadoTecnico)opcao;
}

const char* EstadoTecnicoToStr(EstadoTecnico e) {
    switch (e) {
        case DISPONIVEL: return "Disponível";
        case OCUPADO:    return "Ocupado";
        case FERIAS:     return "Férias";
        case INATIVO:    return "Inativo";   // <-- faltava este caso
        default:         return "Desconhecida";
    }
}

// Menu Técnico
int MenuTecnicos() {
    int a;
    do {
        printf ("\n----- Menu Geral -----");
        printf ("\n1 - Criar Técnico");
        printf ("\n2 - Listar Técnico");
        printf ("\n3 - Eliminar Técnico");
        printf ("\n4 - Gerir Ordens de Manutenção");
        printf ("\n5 - Ativar Técnico");
        printf ("\n0 - Sair");
        printf ("\nEscolha:");
        scanf ("%d", &a);

    } while (a < 0 || a > 5);

    return a;
}