//
// Created by leona on 23/12/2025.
//

#include "leitura_departamentos.h"
#include <cstdlib>
#include <stdio.h>
#include "../../data/structs.h"
#include "../../Departamentos/departamentos.h"

void ListarDepartamentos() {
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
                "%d;%49[^;];%49[^;];%49[^;];%15[^;];%d;%d;",
                &d.IdDept,
                d.nome,
                d.responsavel,
                d.email,
                d.telefone,
                &d.ordens,
                &d.estado
            ) == 7) {

            if (d.estado != Desativado) {
                printf(
                    "\nID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Ordens: %d | Estado: %s\n",
                    d.IdDept,
                    d.nome,
                    d.responsavel,
                    d.email,
                    d.telefone,
                    d.ordens,
                    EstadoParaTexto(d.estado)
                );
            }
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
                "%d;%49[^;];%49[^;];%49[^;];%15[^;];%d;%d;",
                &d.IdDept,
                d.nome,
                d.responsavel,
                d.email,
                d.telefone,
                &d.ordens,
                &d.estado
            ) == 7) {

            if (d.estado == Desativado) {
                printf(
                    "\nID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Ordens: %d | Estado: %s\n",
                    d.IdDept,
                    d.nome,
                    d.responsavel,
                    d.email,
                    d.telefone,
                    d.ordens,
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
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%d;",
                   &lista[n].IdDept,
                   lista[n].nome,
                   lista[n].responsavel,
                   lista[n].email,
                   lista[n].telefone,
                   &lista[n].ordens,
                   &lista[n].estado) == 7) {
            n++;
                   }
    }
    fclose(f);

    // Ordenar a lista pelo número de ordens (decrescente)
    qsort(lista, n, sizeof(Departamento), compararOrdens);

    // Reescrever o ficheiro com a lista ordenada
    f = fopen("../Dados/departamentos.txt", "w");
    if (!f) {
        perror("Erro ao reabrir o ficheiro de departamentos");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%d;%d;\n",
                lista[i].IdDept,
                lista[i].nome,
                lista[i].responsavel,
                lista[i].email,
                lista[i].telefone,
                lista[i].ordens,
                lista[i].estado);
    }

    fclose(f);
    printf("Departamentos ordenados por número de ordens com sucesso.\n");
}

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
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%d;",
                   &d.IdDept,
                   d.nome,
                   d.responsavel,
                   d.email,
                   d.telefone,
                   &d.ordens,
                   &d.estado) == 7) {
            total++;  // conta cada departamento válido
                   } else {
                       printf("Linha de departamento mal formatada ignorada: %s\n", linha);
                   }
    }

    fclose(f);
    return total;
}
