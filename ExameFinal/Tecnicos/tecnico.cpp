/**
* @file tecnico.cpp
 * @author Grupo 37
 * @date 23-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declarações de funções para criar e eliminar técnicos.
 *
 * Este ficheiro contém as declarações das funções utilizadas para gerir técnicos,
 * incluindo criação de um novo técnico e marcação de técnicos como inativos(eliminar tecnicos).
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data/structs.h"
#include "../Menus/Menus Gerais/menus.h"
#include "../Menus/Menus Tecnicos/menus_tecnicos.h"
#include "../Outros/Extra/extra.h"
#include "../Listagem/Tecnicos/leitura_tecnicos.h"
#include "../Tecnicos/tecnico.h"

// --- Criação de um novo técnico ---
Tecnico CriarTecnico() {
    Tecnico t;
    t.IdTecnico = ProximoIdTecnico(); // Gera ID automático
    t.trabalhos = 0; // Inicialmente não tem trabalhos concluídos

    printf("\n----- Menu de Criação -----\n");

    // Alocar memória para o nome do técnico
    t.nome = (char *)malloc(50 * sizeof(char));
    if (t.nome == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    // Limpar buffer do teclado antes de fgets()
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Receber nome do técnico
    printf("Nome do técnico: ");
    fgets(t.nome, 50, stdin);
    t.nome[strcspn(t.nome, "\n")] = 0; // Remove '\n'

    // Seleciona especialidade e estado via menu
    t.especialidade = MenuEspecialidade();
    t.estado = MenuEstado();

    // Mostrar resumo do técnico criado
    printf("Id Tecnico:%d | Nome:%s | Especialidade:%s | Trabalhos Concluídos: %d | Estado:%s\n",
           t.IdTecnico, t.nome,
           EspecialidadeToStr(t.especialidade),
           t.trabalhos,
           EstadoTecnicoToStr(t.estado));

    // Gravar no ficheiro
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "a");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        free(t.nome); // Libertar memória antes de sair
        exit(1);
    }
    fprintf(f, "%d; %s; %s; %d; %s;\n",
            t.IdTecnico,
            t.nome,
            EspecialidadeToStr(t.especialidade),
            t.trabalhos,
            EstadoTecnicoToStr(t.estado));
    fclose(f);

    free(t.nome); // Libertar memória
    t.nome = NULL;

    return t; // Retorna o técnico criado
}

// --- Eliminar um técnico (marcar como INATIVO) ---
void EliminarTecnico() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    printf("Introduza o ID do técnico a eliminar: ");
    scanf("%d", &id);
    getchar(); // Limpar buffer

    Tecnico lista[200];
    int n = 0;
    char bufferNome[256], bufferEsp[50], bufferEst[50];

    // Ler técnicos do ficheiro
    while (fgets(bufferNome, sizeof(bufferNome), f) && n < 200) {
        char linha[512];
        strcpy(linha, bufferNome);

        if (sscanf(linha, "%d ; %255[^;] ; %49[^;] ; %d; %49[^;] ;",
                   &lista[n].IdTecnico,
                   bufferNome,
                   bufferEsp,
                   &lista[n].trabalhos,
                   bufferEst) == 4) {

            // Alocar memória para o nome
            lista[n].nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!lista[n].nome) {
                printf("Erro de memória.\n");
                exit(1);
            }
            strcpy(lista[n].nome, bufferNome);

            // Converter strings para enums
            lista[n].especialidade = StrToEspecialidade(bufferEsp);
            lista[n].estado = StrToEstadoTecnico(bufferEst);

            n++;
        }
    }
    fclose(f);

    // Procurar ID e marcar como INATIVO
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdTecnico == id) {
            lista[i].estado = INATIVO;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Técnico com ID %d não encontrado.\n", id);
        for (int i = 0; i < n; i++)
            free(lista[i].nome); // Libertar memória
        return;
    }

    // Reescrever ficheiro atualizado
    f = fopen("..\\Dados\\tecnicos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        for (int i = 0; i < n; i++)
            free(lista[i].nome);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d; %s; %s; %d; %s;\n",
                lista[i].IdTecnico,
                lista[i].nome,
                EspecialidadeToStr(lista[i].especialidade),
                lista[i].trabalhos,
                EstadoTecnicoToStr(lista[i].estado));
        free(lista[i].nome); // Libertar memória
    }
    fclose(f);

    printf("Técnico com ID %d eliminado.\n", id);
}

// --- Ativar um técnico (marcar como DISPONIVEL) ---
void AtivarTecnico() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    printf("\nIntroduza o Id do Técnico a Ativar: ");
    scanf("%d", &id);
    getchar(); // limpar buffer

    Tecnico lista[200];
    int n = 0;
    char bufferNome[256], bufferEsp[50], bufferEst[50];

    // Ler todos os técnicos
    while (fgets(bufferNome, sizeof(bufferNome), f) && n < 200) {
        char linha[512];
        strcpy(linha, bufferNome);

        if (sscanf(linha, "%d ; %255[^;] ; %49[^;] ; %d ; %49[^;] ;",
                   &lista[n].IdTecnico,
                   bufferNome,
                   bufferEsp,
                   &lista[n].trabalhos,
                   bufferEst) == 5) {

            lista[n].nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!lista[n].nome) {
                printf("Erro de memória.\n");
                exit(1);
            }
            strcpy(lista[n].nome, bufferNome);

            lista[n].especialidade = StrToEspecialidade(bufferEsp);
            lista[n].estado = StrToEstadoTecnico(bufferEst);

            n++;
        }
    }
    fclose(f);

    // Procurar ID e marcar como DISPONIVEL
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdTecnico == id) {
            lista[i].estado = DISPONIVEL;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Técnico com ID %d não encontrado.\n", id);
        for (int i = 0; i < n; i++)
            free(lista[i].nome);
        return;
    }

    // Reescrever ficheiro atualizado
    f = fopen("..\\Dados\\tecnicos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        for (int i = 0; i < n; i++)
            free(lista[i].nome);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d; %s; %s; %d; %s;\n",
                lista[i].IdTecnico,
                lista[i].nome,
                EspecialidadeToStr(lista[i].especialidade),
                lista[i].trabalhos,
                EstadoTecnicoToStr(lista[i].estado));
        free(lista[i].nome);
    }
    fclose(f);

    printf("Técnico com ID %d marcado como Ativo.\n", id);
}

// --- Atualizar o estado de um técnico ---
int AtualizarEstadoTecnico(int idTecnico, EstadoTecnico novoEstado) {
    FILE *f = fopen("../Dados/tecnicos.txt", "r");
    if (!f) {
        perror("Erro ao abrir o ficheiro de técnicos");
        return 0;
    }

    Tecnico tecnicos[200];
    int total = 0;
    int encontrado = 0;

    char linha[512];
    char bufferNome[256], bufferEsp[50], bufferEst[50];

    // Ler todos técnicos do ficheiro
    while (fgets(linha, sizeof(linha), f) && total < 200) {
        if (sscanf(linha, "%d;%255[^;];%49[^;];%d;%49[^;];",
                   &tecnicos[total].IdTecnico,
                   bufferNome,
                   bufferEsp,
                   &tecnicos[total].trabalhos,
                   bufferEst) == 5) {

            tecnicos[total].nome = (char*) malloc(strlen(bufferNome) + 1);
            if (!tecnicos[total].nome) {
                perror("Erro ao alocar memória");
                fclose(f);
                for (int i = 0; i < total; i++)
                    free(tecnicos[i].nome);
                return 0;
            }

            strcpy(tecnicos[total].nome, bufferNome);
            tecnicos[total].especialidade = StrToEspecialidade(bufferEsp);
            tecnicos[total].estado = StrToEstadoTecnico(bufferEst);
            total++;
        }
    }
    fclose(f);

    // Atualizar estado do técnico
    for (int i = 0; i < total; i++) {
        if (tecnicos[i].IdTecnico == idTecnico) {
            if (tecnicos[i].estado == novoEstado) {
                printf("O técnico já se encontra nesse estado.\n");
                goto limpar;
            }
            tecnicos[i].estado = novoEstado;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Técnico não encontrado.\n");
        goto limpar;
    }

    // Escrita segura em ficheiro temporário
    f = fopen("../Dados/tecnicos_tmp.txt", "w");
    if (!f) {
        perror("Erro ao criar ficheiro temporário");
        goto limpar;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%s;%d;%s;\n",
                tecnicos[i].IdTecnico,
                tecnicos[i].nome,
                EspecialidadeToStr(tecnicos[i].especialidade),
                tecnicos[i].trabalhos,
                EstadoTecnicoToStr(tecnicos[i].estado));
    }
    fclose(f);

    remove("../Dados/tecnicos.txt");
    rename("../Dados/tecnicos_tmp.txt", "../Dados/tecnicos.txt");

    printf("Estado do técnico %d atualizado para %s.\n",
           idTecnico, EstadoTecnicoToStr(novoEstado));

limpar:
    // Libertar memória alocada
    for (int i = 0; i < total; i++)
        free(tecnicos[i].nome);

    return encontrado;
}

// --- Incrementa o contador de trabalhos concluídos de um técnico ---
void AdicionarTrabalhos(int Id) {
    FILE *f = fopen("../Dados/tecnicos.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro dos Técnicos");
        return;
    }

    Tecnico tecnicos[200] = {0};
    int total = 0;
    int encontrado = 0;

    char linha[256] = {0};
    char bufferEsp[50] = {0};
    char bufferEst[50] = {0};

    // Ler todos os técnicos
    while (fgets(linha, sizeof(linha), f) && total < 200) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%d;%49[^;];",
                   &tecnicos[total].IdTecnico,
                   tecnicos[total].nome,
                   bufferEsp,
                   &tecnicos[total].trabalhos,
                   bufferEst) == 5) {

            tecnicos[total].especialidade = StrToEspecialidade(bufferEsp);
            tecnicos[total].estado = StrToEstadoTecnico(bufferEst);

            if (tecnicos[total].IdTecnico == Id) {
                tecnicos[total].trabalhos++;
                encontrado = 1;
            }

            total++;
        } else {
            printf("Linha inválida ignorada: %s\n", linha);
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Técnico %d não encontrado.\n", Id);
        return;
    }

    // Reescrever ficheiro atualizado
    f = fopen("../Dados/tecnicos.txt", "w");
    if (!f) {
        perror("Erro ao reabrir ficheiro de Técnicos");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%s;%d;%s;\n",
                tecnicos[i].IdTecnico,
                tecnicos[i].nome,
                EspecialidadeToStr(tecnicos[i].especialidade),
                tecnicos[i].trabalhos,
                EstadoTecnicoToStr(tecnicos[i].estado));
    }

    fclose(f);

    printf("Trabalho adicionado ao técnico %d.\n", Id);
}
