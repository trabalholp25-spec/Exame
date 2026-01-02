//
// Created by leona on 23/12/2025.
//

#include "leitura_departamentos.h"

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
                "%d;%49[^;];%49[^;];%49[^;];%15[^;];%d;",
                &d.IdDept,
                d.nome,
                d.responsavel,
                d.email,
                d.telefone,
                &d.estado
            ) == 6) {

            if (d.estado != Desativado) {
                printf(
                    "\nID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Estado: %s\n",
                    d.IdDept,
                    d.nome,
                    d.responsavel,
                    d.email,
                    d.telefone,
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
                "%d;%49[^;];%49[^;];%49[^;];%15[^;];%d;",
                &d.IdDept,
                d.nome,
                d.responsavel,
                d.email,
                d.telefone,
                &d.estado
            ) == 6) {

            if (d.estado == Desativado) {
                printf(
                    "\nID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Estado: %s\n",
                    d.IdDept,
                    d.nome,
                    d.responsavel,
                    d.email,
                    d.telefone,
                    EstadoParaTexto(d.estado)
                );
            }
            }
    }

    fclose(f);
}