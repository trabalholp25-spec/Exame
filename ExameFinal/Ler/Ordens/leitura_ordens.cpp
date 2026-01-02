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

void ListarOrdens() {

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        exit(1);
    }

    OrdemDeManutencao m;
    char bufferCategoria[50], bufferEstado[50];
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(linha,"%d;%d;%d;%11[^;];%49[^;];%49[^;];%f;",
            &m.IdOrdem,
            &m.IdAtivo,
            &m.IdDepartamento,
            m.DataPedido,
            bufferEstado,   // agora o estado está no 5º campo
            bufferCategoria, // categoria/prioridade fica no 6º campo
            &m.custo)){

            m.estado = StrToEstadoOrdem(bufferEstado);

            printf("\nID da Ordem: %d | Id do Ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Custo: %.2f€",
                   m.IdOrdem,
                   m.IdAtivo,
                   m.IdDepartamento,
                   m.DataPedido,
                   EstadoManutencaoToStr(m.estado),
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
    char bufferCat[50], bufferEst[50];
    char linha[256];

    while (fgets(linha, sizeof(linha), f) && n < 200) {
        if (sscanf(linha,
                   "%d;%d;%d;%11[^;];%49[^;];%49[^;];%f;",
                   &lista[n].IdOrdem,
                   &lista[n].IdAtivo,
                   &lista[n].IdDepartamento,
                   lista[n].DataPedido,
                   bufferCat,
                   bufferEst,
                   &lista[n].custo) == 7) {

            lista[n].estado = StrToEstadoOrdem(bufferCat);
            lista[n].prioridade = StrToPrioridade(bufferEst);

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
        printf("\nID da Ordem: %d | Id do Ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Prioridade: %s | Custo: %.2f€",
               lista[i].IdOrdem,
               lista[i].IdAtivo,
               lista[i].IdDepartamento,
               lista[i].DataPedido,
               EstadoManutencaoToStr(lista[i].estado),
               PrioridadeManutencaoToStr(lista[i].prioridade),
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
    char bufferCategoria[50], bufferEstado[50];
    char linha[256];
    int encontrou = 0;   // contador / flag

    while (fgets(linha, sizeof(linha), f)) {

        if (sscanf(
                linha,
                "%d;%d;%d;%11[^;];%49[^;];%49[^;];%f;",
                &m.IdOrdem,
                &m.IdAtivo,
                &m.IdDepartamento,
                m.DataPedido,
                bufferEstado,
                bufferCategoria,
                &m.custo
            ) == 7) {

            m.estado = StrToEstadoOrdem(bufferEstado);

            // 🔴 só mostra se NÃO estiver concluída
            if (m.estado != Concluido) {
                printf(
                    "\nID da Ordem: %d | Id do Ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Custo: %.2f€",
                    m.IdOrdem,
                    m.IdAtivo,
                    m.IdDepartamento,
                    m.DataPedido,
                    EstadoManutencaoToStr(m.estado),
                    m.custo
                );
                encontrou = 1;
            }
            }
    }

    fclose(f);

    return encontrou;
}

