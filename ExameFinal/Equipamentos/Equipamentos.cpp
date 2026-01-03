/**
 * @file Equipamentos.cpp
 * @author Grupo 37
 * @date 31-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico "ativos"/"equipamentos"
 *
 * Este ficheiro contém as funções utilizadas para gerir os ativos,
 * incluindo criação de um novo ativo e marcação de ativos como inativos(eliminar ativos),
 * e gestão dos mesmos.
 */


#include <stdio.h>
#include "Equipamentos.h"
#include <cstdlib>
#include <cstring>
#include "../Outros/Extra/extra.h"
#include "../Menus/Menus Gerais/menus.h"
#include "../Outros/Verificações/verificacoes.h"
#include "../data/structs.h"
#include "../Menus/Menus Equipamentos/menus_equipamentos.h"
#include "../Listagem/Equipamentos/leitura_equipamentos.h"

#include "departamentos.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "../data/structs.h"
#include "../Outros/Extra/extra.h"
#include "../Outros/Verificações/verificacoes.h"

// --- Função para criar um novo departamento ---
Departamento CriarDepartamento() {
    Departamento d;
    int validar;  // variável para validar email
    int c;        // usado para limpar o buffer do teclado

    // Atribui um ID automático ao departamento
    d.IdDept = ProximoIdDept();
    d.ordens = 0;          // número de ordens inicial
    d.CustoTotal = 0.00;   // custo total inicial
    d.estado = ATIVO;      // estado inicial do departamento

    printf("\n----- Menu de Criação -----\n");

    // Limpa o buffer para evitar problemas com fgets após scanf
    while ((c = getchar()) != '\n' && c != EOF);

    // Lê o nome do departamento
    printf("\nNome do Departamento: ");
    fgets(d.nome, sizeof(d.nome), stdin);
    d.nome[strcspn(d.nome, "\n")] = 0; // remove '\n' do final

    // Lê o nome do responsável pelo departamento
    printf("\nNome do responsável pelo departamento: ");
    fgets(d.responsavel, sizeof(d.responsavel), stdin);
    d.responsavel[strcspn(d.responsavel, "\n")] = 0;

    // Valida o email: repete enquanto o email for inválido
    do {
        printf("\nEmail do departamento: ");
        scanf("%s", d.email);
        validar = ValidarEmail(d.email);
    } while (validar == 0);

    // Limpa buffer novamente
    while ((c = getchar()) != '\n' && c != EOF);

    // Lê o telefone do departamento
    printf("\nTelefone do departamento (+XXXXXXXXXXXX): ");
    fgets(d.telefone, sizeof(d.telefone), stdin);
    d.telefone[strcspn(d.telefone, "\n")] = 0;

    // Mostra os detalhes do departamento criado
    printf("\nDepartamento Criado!\n");
    printf("ID: %d | Nome: %s | Responsável: %s | Email: %s | Telefone: %s | Ordens: %d | Custo Total das Ordens: %.2f €| Estado: %s\n",
           d.IdDept, d.nome, d.responsavel, d.email, d.telefone, d.ordens, d.CustoTotal, EstadoParaTexto(d.estado));

    // Grava os dados do departamento no ficheiro departamentos.txt
    FILE *f = fopen("..\\Dados\\departamentos.txt", "a");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%d;%s;%s;%s;%s;%d;%.2f;%d;\n",
            d.IdDept, d.nome, d.responsavel, d.email, d.telefone, d.ordens, d.CustoTotal, d.estado);

    fclose(f);

    return d;
}

// --- Converte o estado do departamento para texto ---
const char* EstadoParaTexto(EstadoDepartamento estado) {
    if (estado == ATIVO)
        return "Ativo";
    else
        return "Desativado";
}

// --- Desativa um departamento pelo ID ---
void DesativarDepartamento() {
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r"); // abre ficheiro para leitura
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    Departamento lista[100]; // array para guardar todos os departamentos
    int n = 0;               // contador de departamentos
    char linha[256];

    printf("Introduza o ID do departamento a desativar: ");
    scanf("%d", &id);

    // Lê todos os departamentos do ficheiro
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%.2f;%d;",
                &lista[n].IdDept,
                lista[n].nome,
                lista[n].responsavel,
                lista[n].email,
                lista[n].telefone,
                &lista[n].ordens,
                &lista[n].CustoTotal,
                &lista[n].estado
            ) == 8) {
            n++;
        }
    }

    fclose(f);

    // Procura o departamento e marca como DESATIVADO (estado = 1)
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdDept == id) {
            lista[i].estado = Desativado; // alterar estado
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Departamento com ID %d não encontrado.\n", id);
        return;
    }

    // Reescreve todos os departamentos no ficheiro
    f = fopen("..\\Dados\\departamentos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(
            f,
            "%d;%s;%s;%s;%s;%d;%.2f;%d;\n",
            lista[i].IdDept,
            lista[i].nome,
            lista[i].responsavel,
            lista[i].email,
            lista[i].telefone,
            lista[i].ordens,
            lista[i].CustoTotal,
            lista[i].estado
        );
    }

    fclose(f);

    printf("Departamento com ID %d marcado como Desativado.\n", id);
}

// --- Reativa um departamento pelo ID ---
void ReativarDepartamento() {
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    Departamento lista[100];
    int n = 0;
    char linha[256];

    printf("Introduza o ID do departamento a Reativar: ");
    scanf("%d", &id);

    // Lê todos os departamentos
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%.2f;%d;",
                &lista[n].IdDept,
                lista[n].nome,
                lista[n].responsavel,
                lista[n].email,
                lista[n].telefone,
                &lista[n].ordens,
                &lista[n].CustoTotal,
                &lista[n].estado
            ) == 8) {
            n++;
        }
    }

    fclose(f);

    // Procura o departamento e marca como ATIVO (estado = 0)
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

    // Reescreve todos os departamentos no ficheiro
    f = fopen("..\\Dados\\departamentos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(
            f,
            "%d;%s;%s;%s;%s;%d;%.2f;%d;\n",
            lista[i].IdDept,
            lista[i].nome,
            lista[i].responsavel,
            lista[i].email,
            lista[i].telefone,
            lista[i].ordens,
            lista[i].CustoTotal,
            lista[i].estado
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
        float CustoTotal;

        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%.2f;%d;",
                   &idDept, nome, responsavel, email, telefone, &ordens, &CustoTotal, &estado) == 8) {
            if (idDept == id) {
                // Preenche a estrutura apontada por d
                d->IdDept = idDept;
                strcpy(d->nome, nome);
                strcpy(d->responsavel, responsavel);
                strcpy(d->email, email);
                strcpy(d->telefone, telefone);
                d->ordens = ordens;
                d->CustoTotal = CustoTotal;
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
    printf("ID | Nome | Responsável | Email | Telefone | Ordens | Custo Total das Ordens\n");

    while (fgets(linha, sizeof(linha), f)) {
        int id, ordens, estado;
        char nome[50], responsavel[50], email[50], telefone[20];
        float custo;

        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%.2f;%d;",
                   &id, nome, responsavel, email, telefone, &ordens, &custo, &estado) == 8) {
            if (estado == ATIVO) {
                printf("%d | %s | %s | %s | %s | %d | %d\n",
                       id, nome, responsavel, email, telefone, ordens, custo);
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

    while (fgets(linha, sizeof(linha), f) && total < 200) {
        linha[strcspn(linha, "\n")] = 0; // remove '\n'

        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%f;%d",
                   &lista[total].IdDept,
                   lista[total].nome,
                   lista[total].responsavel,
                   lista[total].email,
                   lista[total].telefone,
                   &lista[total].ordens,
                   &lista[total].CustoTotal,
                   &lista[total].estado) == 8) {

            // Se for o departamento certo e ativo, incrementa ordens
            if (lista[total].IdDept == id && lista[total].estado == ATIVO) {
                lista[total].ordens++;
                encontrado = 1;
            }

            total++;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Departamento %d não encontrado ou desativado.\n", id);
        return;
    }

    // Reescreve todos os departamentos no ficheiro
    f = fopen("../Dados/departamentos.txt", "w");
    if (!f) {
        perror("Erro ao reabrir o ficheiro dos Departamentos");
        return;
    }

    for (int i = 0; i < total; i++) {
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

    printf("Ordem adicionada ao Departamento %d.\n", id);
}

// --- Adiciona custo a um departamento ---
void AdicionarCustoDepartamento(int idDept, float valor) {
    if (valor <= 0) return; // ignora valores negativos ou zero

    FILE *f = fopen("../Dados/departamentos.txt", "r");
    FILE *temp = fopen("../Dados/departamentos_tmp.txt", "w");

    if (!f || !temp) {
        perror("Erro ao abrir ficheiros");
        return;
    }

    int IdDept, ordens, estado;
    char nome[50], responsavel[50], email[50], telefone[20];
    float CustoTotal;
    int encontrado = 0;

    // Lê e escreve no ficheiro temporário, adicionando custo ao departamento certo
    while (fscanf(f,
        "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%f;%d;",
        &IdDept, nome, responsavel, email, telefone,
        &ordens, &CustoTotal, &estado) == 8) {

        if (IdDept == idDept) {
            CustoTotal += valor;
            encontrado = 1;
        }

        fprintf(temp,
            "%d;%s;%s;%s;%s;%d;%.2f;%d;\n",
            IdDept, nome, responsavel, email, telefone,
            ordens, CustoTotal, estado);
    }

    fclose(f);
    fclose(temp);

    if (!encontrado) {
        printf("Departamento %d não encontrado.\n", idDept);
        remove("../Dados/departamentos_tmp.txt"); // remove ficheiro temporário
        return;
    }

    // Substitui o ficheiro antigo pelo novo
    remove("../Dados/departamentos.txt");
    rename("../Dados/departamentos_tmp.txt", "../Dados/departamentos.txt");
}

