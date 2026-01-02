/**
* @file tecnico.cpp
 * @author Grupo 37
 * @date 27-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico "técnicos"
 *
 * Este ficheiro contém as funções utilizadas para gerir técnicos,
 * incluindo criação de um novo técnico e marcação de técnicos como inativos(eliminar tecnicos).
 */

#include "tecnico.h"
#include <stdio.h>
#include "../data/structs.h"
#include "../Menus/Menus Gerais/menus.h"
#include <cstdlib>
#include "../Menus/Menus Tecnicos/menus_tecnicos.h"
#include "../extra.h"
#include "../Ler/Tecnicos/leitura_tecnicos.h"

Tecnico CriarTecnico() {
    Tecnico t;
    t.IdTecnico = ProximoIdTecnico(); // Gera o próximo ID disponível

    printf("\n----- Menu de Criação -----\n");

    printf("Nome do técnico: "); // Pergunta o Nome do técnico
    scanf("%49s", t.nome); // Armazena o nome do tecnico

    printf("\nSobrenome do Técnico: "); // Pergunta o Sobrenome do técnico
    scanf("%49s", t.sobrenome); // Armazena o Sobrenome do técnico

    t.especialidade = MenuEspecialidade(); //Esta função está no diretório dos menus, onde o utilizador escolhe a Especialidade do técnico

    t.estado = MenuEstado(); //Esta função está no diretório dos menus, onde o utilizador escolhe o Estado do técnico

    // Mostrar resultado
    printf("Id Tecnico:%d | Nome:%s %s | Especialidade:%s | Estado:%s\n",t.IdTecnico, t.nome,t.sobrenome,EspecialidadeToStr(t.especialidade),EstadoTecnicoToStr(t.estado));


    // --- Gravar no ficheiro ---
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "a"); //Abre o ficheiro "tecnicos.txt" com a permissão "a" (Anexar)
    if (f == NULL) { // Caso não consiga abrir o ficheiro
        perror("Erro ao abrir ficheiro");
        exit(1);
    }

    fprintf(f, "%d; %s; %s; %s; %s;\n",t.IdTecnico, t.nome,t.sobrenome,EspecialidadeToStr(t.especialidade),EstadoTecnicoToStr(t.estado)); // Funcao de escrever no ficheiro

    fclose(f); // Ordem para fechar o .txt
    // --------------------------

    return t;
}

void EliminarTecnico() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r"); //Abre o ficheiro "tecnicos.txt" com a permissão "r" (read)
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n"); // Caso não consiga abrir o ficheiro
        return;
    }

    int id;
    printf("Introduza o ID do técnico a eliminar: "); //Identificar o Id do tecnico a eliminar
    scanf("%d", &id);

    Tecnico lista[200];
    int n = 0;
    char bufferEsp[50], bufferEst[50];

    // Ler técnicos do ficheiro
    while (!feof(f) && n < 200) {
        if (fscanf(f, " %d ; %49[^;] ; %49[^;] ; %49[^;] ;",
                   &lista[n].IdTecnico,
                   lista[n].nome,
                   bufferEsp,
                   bufferEst) == 4) {

            lista[n].especialidade = StrToEspecialidade(bufferEsp);
            lista[n].estado = StrToEstadoTecnico(bufferEst);
            n++;
                   }
    }
    fclose(f);

    // Procurar e marcar como INATIVO
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdTecnico == id) {
            lista[i].estado = INATIVO;
            encontrado = 1;
            break;
        }
    }

    // Caso o Id não seja encontrado
    if (!encontrado) {
        printf("Técnico com ID %d não encontrado.\n", id);
        return;
    }

    // Reescrever o ficheiro
    f = fopen("..\\Dados\\tecnicos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d; %s; %s; %s;\n",
                lista[i].IdTecnico,
                lista[i].nome,
                EspecialidadeToStr(lista[i].especialidade),
                EstadoTecnicoToStr(lista[i].estado));
    }

    fclose(f);

    printf("Técnico com ID %d marcado como Inativo.\n", id);
}
