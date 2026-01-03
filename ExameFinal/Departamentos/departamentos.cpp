/**
* @file departamentos.cpp
 * @author Grupo 37
 * @date 31-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico "departamentos"
 *
 * Este ficheiro contém as funções utilizadas para gerir departamentos,
 * incluindo criação de um novo departamento e marcação de departamentos como inativos(eliminar departamentos).
 */

// Todas as bibliotecas utilizadas
#include "departamentos.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "../data/structs.h"
#include "../extra.h"
#include "../verificacoes.h"

/**
* @file departamentos.cpp
 * @author Grupo 37
 * @date 31-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico "departamentos"
 *
 * Este ficheiro contém as funções utilizadas para gerir departamentos,
 * incluindo criação de um novo departamento e marcação de departamentos como inativos(eliminar departamentos).
 */

// Todas as bibliotecas utilizadas
#include "departamentos.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "../data/structs.h"
#include "../extra.h"
#include "../verificacoes.h"

Departamento CriarDepartamento() {
    // Declaração de variáveis
    Departamento d;
    int validar = 0;
    int ordens = 0;

    d.IdDept = ProximoIdDept(); // Gerar o Id do próximo departamento

    printf("\n----- Menu de Criação -----\n");

    // Limpa buffer antes de fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nNome do Departamento: "); // Nome do Departamento
    fgets(d.nome, sizeof(d.nome), stdin);
    d.nome[strcspn(d.nome, "\n")] = 0;

    printf("\nNome do responsável pelo departamento: "); // Nome do Responsável pelo Departamento
    fgets(d.responsavel, sizeof(d.responsavel), stdin);
    d.responsavel[strcspn(d.responsavel, "\n")] = 0;

    do {
        printf("\nEmail do departamento: "); // Email do Departamento
        scanf("%s", d.email);
        validar = ValidarEmail(d.email); // Verificação do emial (existência de um unico @)
    }while ( validar == 0); // Repete enquanto não for válido

    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nTelefone do departamento(+XXXXXXXXXXXX): "); // Número de telefone
    fgets(d.telefone, sizeof(d.telefone), stdin);
    d.telefone[strcspn(d.telefone, "\n")] = 0;


    d.estado = ATIVO; // Declaração do Estado Inicial

    printf("\nDepartamento Criado!"); // Confirmação da criação
    printf(
        "ID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Ordens: %d|Estado: %d\n",d.IdDept, d.nome, d.responsavel, d.email, d.telefone,d.ordens, EstadoParaTexto(d.estado));

    // Gravar no ficheiro
    FILE *f = fopen("..\\Dados\\departamentos.txt", "a");
    if (f == NULL) {
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%d;%s;%s;%s;%s;%d;%d\n",d.IdDept, d.nome, d.responsavel,  d.email, d.telefone,d.ordens, d.estado);

    fclose(f);

    return d;
}


const char* EstadoParaTexto(EstadoDepartamento estado) {
    if (estado == ATIVO)
        return "Ativo";
    else
        return "Desativado";
}

void DesativarDepartamento() {
    // Abre o ficheiro .txt
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    Departamento lista[100];
    int n = 0;
    char linha[256];

    printf("Introduza o ID do departamento a desativar: "); // Identificar o Id a Desativar
    scanf("%d", &id);

    // Ler todos os departamentos
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%d;",
                &lista[n].IdDept,
                lista[n].nome,
                lista[n].responsavel,
                lista[n].email,
                lista[n].telefone,
                &lista[n].ordens,
                &lista[n].estado
            ) == 7) {

            n++;
            }
    }


    fclose(f);

    // Procurar e marcar como DESATIVADO (1)
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdDept == id) {
            lista[i].estado = Desativado;   // ✅ estado = 1
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Departamento com ID %d não encontrado.\n", id);
        return;
    }

    // Reescrever o ficheiro
    f = fopen("..\\Dados\\departamentos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(
            f,
            "%d;%s;%s;%s;%s;%d;\n",
            lista[i].IdDept,
            lista[i].nome,
            lista[i].responsavel,
            lista[i].email,
            lista[i].telefone,
            lista[i].ordens,
            lista[i].estado   // 0 ou 1
        );
    }

    fclose(f);

    printf("Departamento com ID %d marcado como Desativado.\n", id);
}

void ReativarDepartamento() {
    // Abre o ficheiro .txt
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    Departamento lista[100];
    int n = 0;
    char linha[256];

    printf("Introduza o ID do departamento a Reativar: "); // Identificar o Id a Desativar
    scanf("%d", &id);

    // Ler todos os departamentos
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;",
                &lista[n].IdDept,
                lista[n].nome,
                lista[n].responsavel,
                lista[n].email,
                lista[n].telefone,
                &lista[n].estado
            ) == 6) {

            n++;
            }
    }


    fclose(f);

    // Procurar e marcar como Ativo(0)
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdDept == id) {
            lista[i].estado = ATIVO;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Departamento com ID %d não encontrado.\n", id);
        return;
    }

    // Reescrever o ficheiro
    f = fopen("..\\Dados\\departamentos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(
            f,
            "%d;%s;%s;%s;%s;%d;\n",
            lista[i].IdDept,
            lista[i].nome,
            lista[i].responsavel,
            lista[i].email,
            lista[i].telefone,
            lista[i].estado   // 0 ou 1
        );
    }

    fclose(f);

    printf("Departamento com ID %d marcado como Ativo.\n", id);
}

// --- Obter departamento por ID ---
Departamento* ObterDepartamento(int id, Departamento *d) {
    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro de departamentos.\n");
        return NULL;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        int idDept, ordens, estado;
        char nome[50], responsavel[50], email[50], telefone[20];

        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%d;",
                   &idDept, nome, responsavel, email, telefone, &ordens, &estado) == 7) {
            if (idDept == id) {
                d->IdDept = idDept;
                strcpy(d->nome, nome);
                strcpy(d->responsavel, responsavel);
                strcpy(d->email, email);
                strcpy(d->telefone, telefone);
                d->ordens = ordens;
                d->estado = (EstadoDepartamento)estado;
                fclose(f);
                return d;
            }
        }
    }

    fclose(f);
    return NULL; // Não encontrado
}

// --- Listar apenas departamentos ativos ---
void ListarDepartamentosAtivos() {
    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro de departamentos.\n");
        return;
    }

    char linha[256];
    printf("\n----- Departamentos Ativos -----\n");
    printf("ID | Nome | Responsável | Email | Telefone | Ordens\n");

    while (fgets(linha, sizeof(linha), f)) {
        int id, ordens, estado;
        char nome[50], responsavel[50], email[50], telefone[20];

        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%d;",
                   &id, nome, responsavel, email, telefone, &ordens, &estado) == 7) {
            if (estado == ATIVO) {
                printf("%d | %s | %s | %s | %s | %d\n",
                       id, nome, responsavel, email, telefone, ordens);
            }
        }
    }

    fclose(f);
}

// --- Incrementa ordens de manutenção para um departamento ---
void AdicionarOrdem(int id) {
    Departamento lista[200];
    int total = 0;
    int encontrado = 0;

    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro de departamentos");
        return;
    }

    char linha[256];

    // --- LEITURA ---
    while (fgets(linha, sizeof(linha), f) && total < 200) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%d;",
                   &lista[total].IdDept,
                   lista[total].nome,
                   lista[total].responsavel,
                   lista[total].email,
                   lista[total].telefone,
                   &lista[total].ordens,
                   &lista[total].estado) == 7) {

            if (lista[total].IdDept == id) {
                lista[total].ordens++;  // incrementa o número de ordens
                encontrado = 1;
            }

            total++;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Departamento %d não encontrado.\n", id);
        return;
    }

    // --- REESCRITA ---
    f = fopen("../Dados/departamentos.txt", "w");
    if (!f) {
        perror("Erro ao reabrir o ficheiro dos Departamentos");
        return;
    }

    for (int i = 0; i < total; i++) {
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

    printf("Ordem adicionada ao Departamento %d.\n", id);
}

