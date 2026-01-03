//
// Created by leona on 23/12/2025.
//

#include "leitura_departamentos.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "../../data/structs.h"
#include "../../Departamentos/departamentos.h"

void ListarDepartamentos() {
    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    Departamento d;
    char linha[256];

    printf("\n----- Departamentos Ativos -----\n");

    while (fgets(linha, sizeof(linha), f)) {
        // Remove eventual \n no final
        linha[strcspn(linha, "\n")] = 0;

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

            if (d.estado != Desativado) {
                printf(
                    "ID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Ordens: %d | Custo Total das Ordens: %.2f€ | Estado: %s\n",
                    d.IdDept, d.nome, d.responsavel, d.email, d.telefone, d.ordens, d.CustoTotal,
                    EstadoParaTexto(d.estado)
                );
            }

            } else {
                printf("Linha de departamento mal formatada ignorada: %s\n", linha);
            }
    }

    fclose(f);
}



void ListarDepartamentosDesativados() {
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    Departamento d;
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%15[^;];%d;%.2f;%d;",
                &d.IdDept,
                d.nome,
                d.responsavel,
                d.email,
                d.telefone,
                &d.ordens,
                &d.CustoTotal,
                &d.estado
            ) == 8) {

            if (d.estado == Desativado) {
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

// Função de comparação para qsort (ordena por ordens decrescente)
int compararOrdens(const void *a, const void *b) {
    Departamento *d1 = (Departamento *)a;
    Departamento *d2 = (Departamento *)b;
    return d2->ordens - d1->ordens; // decrescente
}

// Função que ordena departamentos por ordens e reescreve o ficheiro
void OrdenarDepartamentosPorOrdens() {
    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro de departamentos");
        return;
    }

    Departamento lista[200];
    int n = 0;
    char linha[256];

    // Ler todos os departamentos
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

    // Ordenar a lista pelo número de ordens (decrescente)
    qsort(lista, n, sizeof(Departamento), compararOrdens);

    // Mostrar na tela
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

    // Reescrever o ficheiro com a lista ordenada
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
