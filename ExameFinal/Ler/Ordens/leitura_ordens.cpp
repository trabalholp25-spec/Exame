//
// Created by leona on 23/12/2025.
//
#include <stdio.h>
#include "leitura_ordens.h"
#include "../../data/structs.h"
#include <cstdlib>
#include <cstring>
#include "../../Menus/Menus Ordens/menu_ordens.h"

EstadoManutencao StrToEstadoOrdem(const char* s) {
    if (strcmp(s, "Iniciado") == 0) return Iniciado;
    if (strcmp(s, "Decorrer") == 0) return Decorrer;
    if (strcmp(s, "Concluido") == 0) return Concluido;
    return Iniciado; // default
}

PrioridadeManutencao StrToPrioridade(const char *s) {
    if (strcmp(s, "Baixa") == 0) return Baixa;
    if (strcmp(s, "Normal") == 0) return Normal;
    if (strcmp(s, "Alta") == 0) return Alta;
    return Normal; // default
}

TipoManutencao StrToTipo (const char *s) {
    if (strcmp(s, "Corretiva") == 0) return CORRETIVA;
    if (strcmp(s, "Preventiva") == 0) return PREVENTIVA;
    return CORRETIVA; // default
    }


void ListarOrdens() {

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        exit(1);
    }

    OrdemDeManutencao m;
    char bufferCategoria[50], bufferEstado[50], bufferTipo[50];
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(linha,"%d;%d;%d;%11[^;];%49[^;];%49[^;];%49[^;];%f;",
            &m.IdOrdem,
            &m.IdAtivo,
            &m.IdDepartamento,
            m.DataPedido,
            bufferEstado,   // agora o estado está no 5º campo
            bufferCategoria, // categoria/prioridade fica no 6º campo
            bufferTipo,
            &m.custo)){

            m.estado = StrToEstadoOrdem(bufferEstado);
            m.tipo = StrToTipo(bufferTipo);

            printf("\nID da Ordem: %d | Id do Ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Tipo: %s| Custo: %.2f€",
                   m.IdOrdem,
                   m.IdAtivo,
                   m.IdDepartamento,
                   m.DataPedido,
                   EstadoManutencaoToStr(m.estado),
                   TipoManutencaoToStr(m.tipo),
                   m.custo);

                   } else {
                       printf("\nLinha inválida encontrada e ignorada: %s", linha);
                   }
    }

    fclose(f);
}


// Listar só os que estão como iniciando e por prioridade, para se aplicar no iniciar trabalho

int CompararPrioridade(const void* a, const void* b) {
    OrdemDeManutencao* oa = (OrdemDeManutencao*)a;
    OrdemDeManutencao* ob = (OrdemDeManutencao*)b;
    return (int)ob->prioridade - (int)oa->prioridade;
}

void ListarOrdensIniciandoPorPrioridade() {

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        exit(1);
    }

    OrdemDeManutencao lista[200];
    int n = 0;
    char bufferCat[50], bufferEst[50], bufferTipo[50];
    char linha[256];

    while (fgets(linha, sizeof(linha), f) && n < 200) {
        if (sscanf(linha,
                   "%d;%d;%d;%11[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &lista[n].IdOrdem,
                   &lista[n].IdAtivo,
                   &lista[n].IdDepartamento,
                   lista[n].DataPedido,
                   bufferCat,
                   bufferEst,
                   bufferTipo,
                   &lista[n].custo) == 7) {

            lista[n].estado = StrToEstadoOrdem(bufferCat);
            lista[n].prioridade = StrToPrioridade(bufferEst);
            lista[n].tipo = StrToTipo(bufferTipo);

            // Só adiciona se estiver no estado "Iniciado"
            if (lista[n].estado == Iniciado) {
                n++;
            }
        }
    }

    fclose(f);

    // Ordena pelo campo prioridade (Alta > Normal > Baixa)
    qsort(lista, n, sizeof(OrdemDeManutencao), CompararPrioridade);

    printf("\n--- Ordens Iniciando por Prioridade ---\n");

    for (int i = 0; i < n; i++) {
        printf("\nID da Ordem: %d | Id do Ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Prioridade: %s | Tipo: %s | Custo: %.2f€",
               lista[i].IdOrdem,
               lista[i].IdAtivo,
               lista[i].IdDepartamento,
               lista[i].DataPedido,
               EstadoManutencaoToStr(lista[i].estado),
               PrioridadeManutencaoToStr(lista[i].prioridade),
               TipoManutencaoToStr(lista[i].tipo),
               lista[i].custo);
    }

    if (n == 0) {
        printf("\nNão existem ordens com estado 'Iniciado'.\n");
    }
}

int ListarOrdensNaoConcluidas() {

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return 0;
    }

    OrdemDeManutencao m;
    char bufferCategoria[50], bufferEstado[50], bufferTipo[50];
    char linha[256];
    int encontrou = 0;   // contador / flag

    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(
                linha,
                "%d;%d;%d;%11[^;];%49[^;];%49[^;];%49[^;];%f;",
                &m.IdOrdem,
                &m.IdAtivo,
                &m.IdDepartamento,
                m.DataPedido,
                bufferEstado,
                bufferCategoria,
                bufferTipo,
                &m.custo
            ) == 8) {

            m.estado = StrToEstadoOrdem(bufferEstado);
            m.tipo = StrToTipo(bufferTipo);

            if (m.estado == Decorrer) {
                printf(
                    "\nID da Ordem: %d | Id do Ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                    m.IdOrdem,
                    m.IdAtivo,
                    m.IdDepartamento,
                    m.DataPedido,
                    EstadoManutencaoToStr(m.estado),
                    TipoManutencaoToStr(m.tipo),
                    m.custo
                );
                encontrou = 1;
            }
            }
    }

    fclose(f);

    return encontrou;
}

void ListarOrdensPorEstado() {

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return;
    }

    OrdemDeManutencao lista[500];   // buffer temporário
    int total = 0;

    char bufferCategoria[50], bufferEstado[50], bufferTipo[50];
    char linha[256];

    // ===== 1) Ler tudo para memória =====
    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(linha,
                   "%d;%d;%d;%11[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &lista[total].IdOrdem,
                   &lista[total].IdAtivo,
                   &lista[total].IdDepartamento,
                   lista[total].DataPedido,
                   bufferEstado,
                   bufferCategoria,
                   bufferTipo,
                   &lista[total].custo) == 8) {

            lista[total].estado = StrToEstadoOrdem(bufferEstado);
            lista[total].tipo   = StrToTipo(bufferTipo);

            total++;
        }
    }

    fclose(f);

    // ===== 2) Imprimir por categorias =====

    int encontrou;

    printf("\n----- ORDENS INICIADAS -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].estado == Iniciado) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem iniciada!");

    printf("\n----- ORDENS A DECORRER -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].estado == Decorrer) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem a decorrer!");

    printf("\n-----ORDENS CONCLUÍDAS -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].estado == Concluido) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem concluída!");
}

void ListarOrdensPorPrioridade() {

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return;
    }

    OrdemDeManutencao lista[500];   // buffer temporário
    int total = 0;

    char bufferCategoria[50], bufferEstado[50], bufferTipo[50];
    char linha[256];

    // ===== 1) Ler tudo para memória =====
    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(linha,
                   "%d;%d;%d;%11[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &lista[total].IdOrdem,
                   &lista[total].IdAtivo,
                   &lista[total].IdDepartamento,
                   lista[total].DataPedido,
                   bufferEstado,
                   bufferCategoria,
                   bufferTipo,
                   &lista[total].custo) == 8) {

            lista[total].estado = StrToEstadoOrdem(bufferEstado);
            lista[total].prioridade = StrToPrioridade(bufferCategoria);
            lista[total].tipo   = StrToTipo(bufferTipo);

            total++;
        }
    }

    fclose(f);

    // ===== 2) Imprimir por categorias =====

    int encontrou;

    printf("\n----- Prioridade Baixa -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].prioridade == Baixa) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem com prioridade Baixa!");

    printf("\n----- Prioridade Normal -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].prioridade == Normal) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem com prioridade Normal!");

    printf("\n----- Prioridade Alta -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].prioridade == Alta) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem com prioridade Alta!");
}

void ListarOrdensPorTipo() {

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return;
    }

    OrdemDeManutencao lista[500];   // buffer temporário
    int total = 0;

    char bufferCategoria[50], bufferEstado[50], bufferTipo[50];
    char linha[256];

    // ===== 1) Ler tudo para memória =====
    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(linha,
                   "%d;%d;%d;%11[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &lista[total].IdOrdem,
                   &lista[total].IdAtivo,
                   &lista[total].IdDepartamento,
                   lista[total].DataPedido,
                   bufferEstado,
                   bufferCategoria,
                   bufferTipo,
                   &lista[total].custo) == 8) {

            lista[total].estado = StrToEstadoOrdem(bufferEstado);
            lista[total].prioridade = StrToPrioridade(bufferCategoria);
            lista[total].tipo   = StrToTipo(bufferTipo);

            total++;
        }
    }

    fclose(f);

    // ===== 2) Imprimir por tipo =====

    int encontrou;

    printf("\n----- Tipo Corretivo -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].tipo == CORRETIVA) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem de tipo Corretiva!");

    printf("\n----- Tipo Preventiva -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].tipo == PREVENTIVA) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem de tipo Preventiva!");
}

void ListarOrdensConcluidas(){

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return;
    }

    OrdemDeManutencao lista[500];   // buffer temporário
    int total = 0;

    char bufferCategoria[50], bufferEstado[50], bufferTipo[50];
    char linha[256];

    // ===== 1) Ler tudo para memória =====
    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(linha,
                   "%d;%d;%d;%11[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &lista[total].IdOrdem,
                   &lista[total].IdAtivo,
                   &lista[total].IdDepartamento,
                   lista[total].DataPedido,
                   bufferEstado,
                   bufferCategoria,
                   bufferTipo,
                   &lista[total].custo) == 8) {

            lista[total].estado = StrToEstadoOrdem(bufferEstado);
            lista[total].prioridade = StrToPrioridade(bufferCategoria);
            lista[total].tipo   = StrToTipo(bufferTipo);

            total++;
        }
    }

    fclose(f);

    // ===== 2) Imprimir por Estado =====

    int encontrou;

    printf("\n----- Tipo Corretivo -----");
    encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].estado == Concluido) {
            printf("\nID: %d | Ativo: %d | Dep: %d | Data: %s | Estado: %s | Tipo: %s | Custo: %.2f€",
                   lista[i].IdOrdem, lista[i].IdAtivo, lista[i].IdDepartamento,
                   lista[i].DataPedido,
                   EstadoManutencaoToStr(lista[i].estado),
                   TipoManutencaoToStr(lista[i].tipo),
                   lista[i].custo);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("\nNenhuma ordem concluída");

}