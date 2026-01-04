/**
* @file leitura_equipamentos.h
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico da listagem de equipamentos/ativos.
 *
 * Este ficheiro contém as funções utilizadas para listar Equipamentos com/sem filtros.
 */
#include "leitura_equipamentos.h"

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "../../data/structs.h"
#include "../../Menus/Menus Equipamentos/menus_equipamentos.h"

// Ativos / Equipamentos
// Função para listar todos os ativos que não estão inativos
void ListarAtivos() {
    FILE *f = fopen("../Dados/ativos.txt", "r"); // Abre o ficheiro em modo leitura
    if (!f) { // Verifica se o ficheiro foi aberto corretamente
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    Ativo a;                  // Estrutura para armazenar os dados de cada ativo
    char bufferCat[50], bufferEst[50]; // Buffers temporários para categoria e estado
    char linha[256];          // Buffer para ler cada linha do ficheiro

    // Lê cada linha do ficheiro
    while (fgets(linha, sizeof(linha), f)) {
        // Faz parsing da linha; espera 7 campos separados por ';'
        if (sscanf(linha,"%d;%49[^;];%49[^;];%11[^;];%49[^;];%49[^;];%d;",
                   &a.IdAtv,a.nome,a.localizacao,a.data,bufferCat,bufferEst,&a.reparos) == 7) {

            // Converte strings para enums
            a.categoria = StrToCategoria(bufferCat);
            a.estado = StrToEstadoAtivo(bufferEst);

            // Só mostra se o ativo não estiver Inativo
            if (a.estado != Inativo) {
                printf("Id:%d | Nome:%s | Localização:%s | Categoria:%s | Estado:%s | Reparações:%d\n",
                       a.IdAtv,
                       a.nome,
                       a.localizacao,
                       CategoriaToStr(a.categoria),
                       EstadoAtivoToStr(a.estado),
                       a.reparos);
            }
        }
    }

    fclose(f); // Fecha o ficheiro
}

// Função para listar ativos agrupados por estado
void ListarAtivosPorEstado() {
    FILE *f = fopen("..\\Dados\\ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    // Array de estados que queremos listar
    EstadoEquipamento estados[] = { Operacional, EmOperacao, EmReparacao, Abatido };
    int totalEstados = sizeof(estados) / sizeof(estados[0]);

    // Para cada estado
    for (int i = 0; i < totalEstados; i++) {
        printf("\n===== Ativos %s =====\n", EstadoAtivoToStr(estados[i]));

        rewind(f); // Volta ao início do ficheiro

        Ativo a;
        char bufferCat[50], bufferEst[50];
        char linha[256];
        int encontrou = 0; // Flag para indicar se encontrou ativos deste estado

        while (fgets(linha, sizeof(linha), f)) {
            // Parsing da linha
            if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                       &a.IdAtv,a.nome,a.localizacao,a.data,bufferCat,bufferEst,&a.reparos) == 7) {

                a.categoria = StrToCategoria(bufferCat);
                a.estado = StrToEstadoAtivo(bufferEst);

                // Se o ativo estiver no estado atual, mostra
                if (a.estado == estados[i]) {
                    printf("Id:%d | Nome:%s | Localização:%s | Categoria:%s\n | Reparações: %d\n",
                           a.IdAtv, a.nome, a.localizacao,
                           CategoriaToStr(a.categoria), a.reparos);
                    encontrou = 1;
                }
            }
        }

        if (!encontrou) {
            printf("Nenhum ativo neste estado.\n");
        }
    }

    fclose(f);
}

// Função para listar ativos agrupados por categoria
void ListarAtivosPorCategoria() {
    FILE *f = fopen("..\\Dados\\ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    // Array de categorias
    CategoriaAtivo categorias[] = { VIATURA, EQUIPAMENTO_INFORMATICO, MOBILIARIO_URBANO, FERRAMENTA, OUTRA };
    int totalCategorias = sizeof(categorias) / sizeof(categorias[0]);

    for (int i = 0; i < totalCategorias; i++) {
        printf("\n===== Ativos da categoria %s =====\n", CategoriaToStr(categorias[i]));
        rewind(f); // Volta ao início do ficheiro

        Ativo a;
        char bufferCat[50], bufferEst[50];
        char linha[256];
        int encontrou = 0;

        while (fgets(linha, sizeof(linha), f)) {
            if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                       &a.IdAtv,a.nome,a.localizacao,a.data,bufferCat,bufferEst,&a.reparos) == 7) {

                a.categoria = StrToCategoria(bufferCat);
                a.estado = StrToEstadoAtivo(bufferEst);

                // Só mostra ativos da categoria atual e que não estejam inativos
                if (a.categoria == categorias[i] && a.estado != Inativo) {
                    printf("Id:%d | Nome:%s | Localização:%s | Estado:%s | Reparações: %d\n",
                           a.IdAtv,a.nome,a.localizacao,EstadoAtivoToStr(a.estado),a.reparos);
                    encontrou = 1;
                }
            }
        }

        if (!encontrou) {
            printf("Nenhum ativo nesta categoria.\n");
        }
    }

    fclose(f);
}

// Converte string para enum EstadoEquipamento
EstadoEquipamento StrToEstadoAtivo(const char* s) {
    if (strcmp(s, "Disponível") == 0) return Operacional;
    if (strcmp(s, "Em Operação") == 0) return EmOperacao;
    if (strcmp(s, "Em Reparação") == 0) return EmReparacao;
    if (strcmp(s, "Abatido") == 0) return Abatido;
    if (strcmp(s, "Inativo") == 0) return Inativo;
    return Inativo; // Caso desconhecido
}

// Converte string para enum CategoriaAtivo
CategoriaAtivo StrToCategoria(const char *s) {
    if (strcmp(s, "Viatura") == 0) return VIATURA;
    if (strcmp(s, "Equipamento Informático") == 0) return EQUIPAMENTO_INFORMATICO;
    if (strcmp(s, "Mobiliário Urbano") == 0) return MOBILIARIO_URBANO;
    if (strcmp(s, "Ferramenta") == 0) return FERRAMENTA;
    if (strcmp(s, "Outra") == 0) return OUTRA;
    return OUTRA; // Caso desconhecido
}

// Conta quantos ativos existem no ficheiro
int AtivosExistentes() {
    Ativo a;
    char bufferCat[50] = {0}, bufferEst[50] = {0};
    char linha[256] = {0};
    int total = 0;

    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                   &a.IdAtv,a.nome,a.localizacao,a.data,bufferCat,bufferEst,&a.reparos) == 7) {
            total++;  // Conta cada ativo válido
        } else {
            printf("Linha de ativo mal formatada ignorada: %s\n", linha);
        }
    }

    fclose(f);
    return total;
}

// Função de comparação para qsort - ordena por número de reparos decrescente
int CompararAtivosPorReparos(const void *a, const void *b) {
    Ativo *atv1 = (Ativo *)a;
    Ativo *atv2 = (Ativo *)b;
    return atv2->reparos - atv1->reparos; // ordem decrescente
}

// Lista ativos ordenados pelo número de reparos
void ListarAtivosPorReparos() {
    Ativo lista[200]; // Limite de 200 ativos
    int total = 0;

    char bufferCat[50] = {0}, bufferEst[50] = {0};
    char linha[256] = {0};

    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    // Lê ativos do ficheiro
    while (fgets(linha, sizeof(linha), f) && total < 200) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                   &lista[total].IdAtv, lista[total].nome, lista[total].localizacao,
                   lista[total].data, bufferCat, bufferEst, &lista[total].reparos) == 7) {

            lista[total].categoria = StrToCategoria(bufferCat);
            lista[total].estado    = StrToEstadoAtivo(bufferEst);
            total++;
        } else {
            printf("Linha de ativo mal formatada ignorada: %s\n", linha);
        }
    }

    fclose(f);

    if (total == 0) {
        printf("Nenhum ativo encontrado.\n");
        return;
    }

    // Ordena por número de reparos decrescente
    qsort(lista, total, sizeof(Ativo), CompararAtivosPorReparos);

    // Lista os ativos ordenados
    printf("\n--- Ativos ordenados por número de reparos ---\n");
    printf("ID | Nome | Localização | Reparos Corretivos | Estado\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%d | %s | %s | %d | %s\n",
               lista[i].IdAtv,
               lista[i].nome,
               lista[i].localizacao,
               lista[i].reparos,
               EstadoAtivoToStr(lista[i].estado));
    }
}

