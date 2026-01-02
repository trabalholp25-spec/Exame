//
// Created by leona on 23/12/2025.
//

#include "leitura_equipamentos.h"

#include <cstring>
#include <stdio.h>
#include "../../data/structs.h"
#include "../../Menus/Menus Equipamentos/menus_equipamentos.h"

// Ativos / Equipamentos

void ListarAtivos() {
    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    Ativo a;
    char bufferCat[50], bufferEst[50];
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha,"%d;%49[^;];%49[^;];%11[^;];%49[^;];%49[^;];%d;",&a.IdAtv,a.nome,a.localizacao,a.data,bufferCat,bufferEst,&a.reparos) == 7) {

            a.categoria = StrToCategoria(bufferCat);
            a.estado = StrToEstadoAtivo(bufferEst);

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

    fclose(f);
}

// Listar Ativos por estado
void ListarAtivosPorEstado() {
    FILE *f = fopen("..\\Dados\\ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    EstadoEquipamento estados[] = {
        Operacional,
        EmOperacao,
        EmReparacao,
        Abatido
    };

    int totalEstados = sizeof(estados) / sizeof(estados[0]);

    for (int i = 0; i < totalEstados; i++) {
        printf("\n===== Ativos %s =====\n", EstadoAtivoToStr(estados[i]));

        rewind(f); // volta ao início do ficheiro

        Ativo a;
        char bufferCat[50], bufferEst[50];
        char linha[256];
        int encontrou = 0;

        while (fgets(linha, sizeof(linha), f)) {
            if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                       &a.IdAtv,
                       a.nome,
                       a.localizacao,
                       a.data,
                       bufferCat,
                       bufferEst,
                       a.reparos) == 7) {

                a.categoria = StrToCategoria(bufferCat);
                a.estado = StrToEstadoAtivo(bufferEst);

                if (a.estado == estados[i]) {
                    printf("Id:%d | Nome:%s | Localização:%s | Categoria:%s\n | Reparações: %d\n",
                           a.IdAtv,
                           a.nome,
                           a.localizacao,
                           CategoriaToStr(a.categoria),
                           a.reparos);
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
// Listar Ativos por Categorias
void ListarAtivosPorCategoria() {
    FILE *f = fopen("..\\Dados\\ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    CategoriaAtivo categorias[] = {
        VIATURA,
        EQUIPAMENTO_INFORMATICO,
        MOBILIARIO_URBANO,
        FERRAMENTA,
        OUTRA
    };

    int totalCategorias = sizeof(categorias) / sizeof(categorias[0]);

    for (int i = 0; i < totalCategorias; i++) {
        printf("\n===== Ativos da categoria %s =====\n", CategoriaToStr(categorias[i]));

        rewind(f);

        Ativo a;
        char bufferCat[50], bufferEst[50];
        char linha[256];
        int encontrou = 0;

        while (fgets(linha, sizeof(linha), f)) {
            if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                       &a.IdAtv,
                       a.nome,
                       a.localizacao,
                       a.data,
                       bufferCat,
                       bufferEst,
                       &a.reparos) == 7) {

                a.categoria = StrToCategoria(bufferCat);
                a.estado = StrToEstadoAtivo(bufferEst);

                if (a.categoria == categorias[i] && a.estado != Inativo) {
                    printf("Id:%d | Nome:%s | Localização:%s | Estado:%s | Reparações: %d\n",
                           a.IdAtv,
                           a.nome,
                           a.localizacao,
                           EstadoAtivoToStr(a.estado),
                           a.reparos);
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

EstadoEquipamento StrToEstadoAtivo(const char* s) {
    if (strcmp(s, "Disponível") == 0) return Operacional;
    if (strcmp(s, "Em Operação") == 0) return EmOperacao;
    if (strcmp(s, "Em Reparação") == 0) return EmReparacao;
    if (strcmp(s, "Abatido") == 0) return Abatido;
    if (strcmp(s, "Inativo") == 0) return Inativo;
    return Inativo; // Desconhecida
}

CategoriaAtivo StrToCategoria(const char *s) {
    if (strcmp(s, "Viatura") == 0) return VIATURA;
    if (strcmp(s, "Equipamento Informático") == 0) return EQUIPAMENTO_INFORMATICO;
    if (strcmp(s, "Mobiliário Urbano") == 0) return MOBILIARIO_URBANO;
    if (strcmp(s, "Ferramenta") == 0) return FERRAMENTA;
    if (strcmp(s, "Outra") == 0) return OUTRA;
    return OUTRA; // Desconhecida
}