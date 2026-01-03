//
// Created by leona on 23/12/2025.
//
#include <stdio.h>
#include "../../Menus/Menus Tecnicos/menus_tecnicos.h"
#include "leitura_tecnicos.h"
#include "../../data/structs.h"

#include <cstdlib>
#include <cstring>

void ListarTecnicos() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        exit(EXIT_FAILURE);
    }

    Tecnico t;
    char bufferNome[256], bufferEsp[50], bufferEst[50];
    char linha[512];

    while (fgets(linha, sizeof(linha), f)) {
        // Ler a linha do ficheiro
        if (sscanf(linha, "%d; %255[^;]; %49[^;]; %d; %49[^;];",
                   &t.IdTecnico, bufferNome, bufferEsp, &t.trabalhos, bufferEst) == 5) {

            // Alocar memória dinamicamente para o nome
            t.nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!t.nome) {
                printf("Erro de memória.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(t.nome, bufferNome);

            // Converter strings para enum
            t.especialidade = StrToEspecialidade(bufferEsp);
            t.estado = StrToEstadoTecnico(bufferEst);

            if (t.estado != INATIVO) {
                printf("Id:%d | Nome:%s | Especialidade:%s | Trabalhos Concluídos:%d | Estado:%s\n",
                       t.IdTecnico,
                       t.nome,
                       EspecialidadeToStr(t.especialidade),
                       t.trabalhos,
                       EstadoTecnicoToStr(t.estado));
            }

            free(t.nome); // Libertar memória
                   }
    }

    fclose(f);
}

EstadoTecnico StrToEstadoTecnico(const char *s) {
    if (!s) return INATIVO;

    if (strcasecmp(s, "DISPONIVEL") == 0 ||
        strcasecmp(s, "Disponivel") == 0 ||
        strcasecmp(s, "Disponível") == 0)
        return DISPONIVEL;

    if (strcasecmp(s, "OCUPADO") == 0 ||
        strcasecmp(s, "Ocupado") == 0)
        return OCUPADO;

    if (strcasecmp(s, "FERIAS") == 0 ||
        strcasecmp(s, "Férias") == 0)
        return FERIAS;

    if (strcasecmp(s, "INATIVO") == 0 ||
        strcasecmp(s, "Inativo") == 0)
        return INATIVO;

    return INATIVO;
}


Especialidade StrToEspecialidade(const char *s) {
    if (strcmp(s, "Eletricista") == 0) return ELETRICISTA;
    if (strcmp(s, "Mecânico") == 0)    return MECANICO;
    if (strcmp(s, "Informático") == 0) return INFORMATICO;
    if (strcmp(s, "Pedreiro") == 0)    return PEDREIRO;
    if (strcmp(s, "Pintor") == 0)      return PINTOR;
    if (strcmp(s, "Outro") == 0)       return OUTRO;
    return OUTRO; // default
}

void ListarTecnicosInativos() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        exit(EXIT_FAILURE);
    }

    Tecnico t;
    char bufferNome[256], bufferEsp[50], bufferEst[50];
    char linha[512];

    while (fgets(linha, sizeof(linha), f)) {
        // Ler a linha do ficheiro
        if (sscanf(linha, "%d; %255[^;]; %49[^;]; %d; %49[^;];",
                   &t.IdTecnico, bufferNome, bufferEsp, &t.trabalhos , bufferEst) == 5) {

            // Alocar memória dinamicamente para o nome
            t.nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!t.nome) {
                printf("Erro de memória.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(t.nome, bufferNome);

            // Converter strings para enum
            t.especialidade = StrToEspecialidade(bufferEsp);
            t.estado = StrToEstadoTecnico(bufferEst);

            if (t.estado == INATIVO) {
                printf("Id:%d | Nome:%s | Especialidade:%s | Trabalhos Concluídos:%d | Estado:%s\n",
                       t.IdTecnico,
                       t.nome,
                       EspecialidadeToStr(t.especialidade),
                       t.trabalhos,
                       EstadoTecnicoToStr(t.estado));
            }

            free(t.nome); // Libertar memória
                   }
    }

    fclose(f);
}

void ListarTecnicosPorCategoria() {
    FILE *f;
    Tecnico t;
    char bufferNome[256], bufferEsp[50], bufferEst[50];
    char linha[512];

    // Percorrer todas as especialidades
    for (int esp = ELETRICISTA; esp <= OUTRO; esp++) {
        Especialidade e = (Especialidade)esp;

        printf("\n----- Especialidade: %s -----\n", EspecialidadeToStr(e));

        f = fopen("..\\Dados\\tecnicos.txt", "r");

        while (fgets(linha, sizeof(linha), f)) {

            if (sscanf(linha, "%d; %255[^;]; %49[^;]; %d; %49[^;];",
                       &t.IdTecnico, bufferNome, bufferEsp, &t.trabalhos, bufferEst) == 5) {

                t.especialidade = StrToEspecialidade(bufferEsp);
                t.estado = StrToEstadoTecnico(bufferEst);

                if (t.especialidade == esp) {

                    t.nome = (char *)malloc(strlen(bufferNome) + 1);
                    if (!t.nome) {
                        printf("Erro de memória.\n");
                        fclose(f);
                        return;
                    }
                    strcpy(t.nome, bufferNome);

                    printf("Id:%d | Nome:%s | Estado:%s | Trabalhos Concluídos:%d\n",
                           t.IdTecnico,
                           t.nome,
                           EstadoTecnicoToStr(t.estado),
                           t.trabalhos);

                    free(t.nome);
                }
                       }
            fclose(f);
        }
    }
}

void ListarTecnicosPorDisp() {
    FILE *f;
    Tecnico t;
    char bufferNome[256], bufferEsp[50], bufferEst[50];
    char linha[512];

    // Percorrer todas as especialidades
    for (int est = DISPONIVEL; est <= INATIVO; est++) {
        EstadoTecnico e = (EstadoTecnico)est;

        printf("\n----- Disponibilidade: %s -----\n", EstadoTecnicoToStr(e));

        f = fopen("..\\Dados\\tecnicos.txt", "r");

        while (fgets(linha, sizeof(linha), f)) {

            if (sscanf(linha, "%d; %255[^;]; %49[^;]; %d; %49[^;];",
                       &t.IdTecnico, bufferNome, bufferEsp, &t.trabalhos, bufferEst) == 5) {

                t.especialidade = StrToEspecialidade(bufferEsp);
                t.estado = StrToEstadoTecnico(bufferEst);

                if (t.estado == est) {

                    t.nome = (char *)malloc(strlen(bufferNome) + 1);
                    if (!t.nome) {
                        printf("Erro de memória.\n");
                        fclose(f);
                        return;
                    }
                    strcpy(t.nome, bufferNome);

                    printf("Id:%d | Nome:%s | Especialidade:%s | Trabalhos Concluídos:%d\n",
                           t.IdTecnico,
                           t.nome,
                           EspecialidadeToStr(t.especialidade),
                           t.trabalhos);

                    free(t.nome);
                }
                       }
            fclose(f);
        }
    }
}