//
// Created by leona on 23/12/2025.
//

#include "leitura_equipamentos.h"

#include <cstdlib>
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
                   &a.IdAtv,
                   a.nome,
                   a.localizacao,
                   a.data,
                   bufferCat,
                   bufferEst,
                   &a.reparos) == 7) {
            total++;  // conta cada ativo válido
                   } else {
                       printf("Linha de ativo mal formatada ignorada: %s\n", linha);
                   }
    }

    fclose(f);
    return total;
}


int CompararAtivosPorReparos(const void *a, const void *b) {
    Ativo *atv1 = (Ativo *)a;
    Ativo *atv2 = (Ativo *)b;

    // ordem decrescente
    return atv2->reparos - atv1->reparos;
}

void ListarAtivosPorReparos() {
    Ativo lista[200];
    int total = 0;

    char bufferCat[50] = {0}, bufferEst[50] = {0};
    char linha[256] = {0};

    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    // Ler ativos
    while (fgets(linha, sizeof(linha), f) && total < 200) {

        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                   &lista[total].IdAtv,
                   lista[total].nome,
                   lista[total].localizacao,
                   lista[total].data,
                   bufferCat,
                   bufferEst,
                   &lista[total].reparos) == 7) {

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

    // Ordenar por número de reparos
    qsort(lista, total, sizeof(Ativo), CompararAtivosPorReparos);

    // Listar na tela
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
