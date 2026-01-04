/**
* @file leitura_departamentos.cpp
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico da listagem de departamentos.
 *
 * Este ficheiro contém as funções utilizadas para listar Departamentos com/sem filtros.
 */



#include "leitura_departamentos.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "../../data/structs.h"
#include "../../Departamentos/departamentos.h"

// Lista todos os departamentos ativos (não desativados)
void ListarDepartamentos() {
    FILE *f = fopen("../Dados/departamentos.txt", "r"); // abre ficheiro de departamentos
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    Departamento d;
    char linha[256];

    printf("\n----- Departamentos Ativos -----\n");

    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0; // remove '\n' no final da linha

        // Faz parsing da linha do ficheiro para a struct Departamento
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%f;%d;",
                &d.IdDept,
                d.nome,
                d.responsavel,
                d.email,
                d.telefone,
                &d.ordens,
                &d.CustoTotal,
                &d.estado
            ) == 8) {

            if (d.estado != Desativado) { // apenas mostra ativos
                printf(
                    "ID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Ordens: %d | Custo Total das Ordens: %.2f€ | Estado: %s\n",
                    d.IdDept, d.nome, d.responsavel, d.email, d.telefone, d.ordens, d.CustoTotal,
                    EstadoParaTexto(d.estado) // converte enum para texto
                );
            }

            } else {
                printf("Linha de departamento mal formatada ignorada: %s\n", linha); // aviso se linha inválida
            }
    }

    fclose(f); // fechar ficheiro
}
// Lista todos os departamentos que estão desativados
void ListarDepartamentosDesativados() {
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    Departamento d;
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {
        int estadoInt;

        // Ler linha e extrair todos os campos, incluindo estado como inteiro
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%15[^;];%d; %f;%d;",
                &d.IdDept,
                d.nome,
                d.responsavel,
                d.email,
                d.telefone,
                &d.ordens,
                &d.CustoTotal,
                &estadoInt
            ) == 8) {

            d.estado = (EstadoDepartamento)estadoInt; // converte para enum

            if (d.estado == Desativado) { // apenas desativados
                printf(
                    "\nID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Ordens: %d | Custo Total das Ordens: %.2f€ | Estado: %s\n",
                    d.IdDept,
                    d.nome,
                    d.responsavel,
                    d.email,
                    d.telefone,
                    d.ordens,
                    d.CustoTotal,
                    EstadoParaTexto(d.estado)
                );
            }
            }
    }

    fclose(f);
}

// Função de comparação para qsort (ordena departamentos por número de ordens, decrescente)
int compararOrdens(const void *a, const void *b) {
    Departamento *d1 = (Departamento *)a;
    Departamento *d2 = (Departamento *)b;
    return d2->ordens - d1->ordens; // decrescente
}

// Ordena os departamentos pelo número de ordens e reescreve o ficheiro
void OrdenarDepartamentosPorOrdens() {
    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro de departamentos");
        return;
    }

    Departamento lista[200];
    int n = 0;
    char linha[256];

    // Ler todos os departamentos do ficheiro
    while (fgets(linha, sizeof(linha), f) && n < 200) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%.2f;%d;",
                   &lista[n].IdDept,
                   lista[n].nome,
                   lista[n].responsavel,
                   lista[n].email,
                   lista[n].telefone,
                   &lista[n].ordens,
                   &lista[n].CustoTotal,
                   &lista[n].estado) == 8) {
            n++;
        }
    }
    fclose(f);

    // Ordenar a lista pelo número de ordens
    qsort(lista, n, sizeof(Departamento), compararOrdens);

    // Mostrar departamentos ordenados
    printf("\n--- Departamentos ordenados por número de ordens ---\n");
    printf("ID | Nome | Responsável | Email | Telefone | Ordens | Custo Total das Ordens | Estado\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d | %s | %s | %s | %s | %d | %.2f | %d\n",
               lista[i].IdDept,
               lista[i].nome,
               lista[i].responsavel,
               lista[i].email,
               lista[i].telefone,
               lista[i].ordens,
               lista[i].CustoTotal,
               lista[i].estado);
    }

    // Reescrever ficheiro com a lista ordenada
    f = fopen("../Dados/departamentos.txt", "w");
    if (!f) {
        perror("Erro ao reabrir o ficheiro de departamentos");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%d;%.2f;%d;\n",
                lista[i].IdDept,
                lista[i].nome,
                lista[i].responsavel,
                lista[i].email,
                lista[i].telefone,
                lista[i].ordens,
                lista[i].CustoTotal,
                lista[i].estado);
    }

    fclose(f);
    printf("\nDepartamentos ordenados por número de ordens com sucesso.\n");
}


// Lista todos os departamentos existentes
int DepartamentosExistentes() {
    Departamento d;
    char linha[256] = {0};
    int total = 0;

    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro de departamentos.\n");
        return 0;
    }

    // Ler cada linha e contar departamentos válidos
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%2.f;%d;",
                   &d.IdDept,
                   d.nome,
                   d.responsavel,
                   d.email,
                   d.telefone,
                   &d.ordens,
                   &d.CustoTotal,
                   &d.estado) == 8) {
            total++;  // conta cada departamento válido
                   } else {
                       printf("Linha de departamento mal formatada ignorada: %s\n", linha);
                   }
    }

    fclose(f);
    return total;
}
