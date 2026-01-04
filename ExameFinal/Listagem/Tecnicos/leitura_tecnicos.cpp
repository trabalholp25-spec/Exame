/**
* @file leitura_tecnicos.cpp
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico da listagem de tecnicos.
 *
 * Este ficheiro contém funções utilizadas para listar os técnicos,
 * podendo aplicar filtros por estado, etc...
 */

#include <stdio.h>
#include "../../Menus/Menus Tecnicos/menus_tecnicos.h"
#include "leitura_tecnicos.h"
#include "../../data/structs.h"
#include <cstdlib>
#include <cstring>



// ---------------------- LISTAR TODOS OS TÉCNICOS ----------------------
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
        if (sscanf(linha, "%d; %255[^;]; %49[^;]; %d; %49[^;];",
                   &t.IdTecnico, bufferNome, bufferEsp, &t.trabalhos, bufferEst) == 5) {

            t.nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!t.nome) {
                printf("Erro de memória.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(t.nome, bufferNome);

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

            free(t.nome);
        }
    }

    fclose(f);
}

// ---------------------- CONVERSÕES ----------------------
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
    return OUTRO;
}

// ---------------------- LISTAR TÉCNICOS INATIVOS ----------------------
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
        if (sscanf(linha, "%d; %255[^;]; %49[^;]; %d; %49[^;];",
                   &t.IdTecnico, bufferNome, bufferEsp, &t.trabalhos , bufferEst) == 5) {

            t.nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!t.nome) {
                printf("Erro de memória.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(t.nome, bufferNome);

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

            free(t.nome);
        }
    }

    fclose(f);
}

// ---------------------- LISTAR POR ESPECIALIDADE ----------------------
void ListarTecnicosPorCategoria() {
    FILE *f;
    Tecnico t;
    char bufferNome[256], bufferEsp[50], bufferEst[50];
    char linha[512];

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
        }
        fclose(f);
    }
}

// ---------------------- LISTAR POR DISPONIBILIDADE ----------------------
void ListarTecnicosPorDisp() {
    FILE *f;
    Tecnico t;
    char bufferNome[256], bufferEsp[50], bufferEst[50];
    char linha[512];

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
        }
        fclose(f);
    }
}
