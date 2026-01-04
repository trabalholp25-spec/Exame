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
#include "../Outros/Extra/extra.h"
#include "../Outros/Verificações/verificacoes.h"
#include <cstring>

#include "../Listagem/Departamentos/leitura_departamentos.h"
#include "../Logs/Funcoes/Logs.h"

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
    do {
        printf("\nNome do Departamento: ");
        fgets(d.nome, sizeof(d.nome), stdin);
        d.nome[strcspn(d.nome, "\n")] = 0;
    } while (strlen(d.nome) == 0);

    // Lê o nome do responsável pelo departamento
    do {
        printf("\nNome do responsável pelo departamento: ");
        fgets(d.responsavel, sizeof(d.responsavel), stdin);
        d.responsavel[strcspn(d.responsavel, "\n")] = 0;
    } while (strlen(d.responsavel) == 0);


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

    // Logs
    char log[200];
    sprintf(log, "Departamento criado | ID: %d | Nome: %s | Responsável: %s | Email: %s",
            d.IdDept, d.nome, d.responsavel, d.email);
    RegistarLog(log);

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
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    Departamento lista[100];
    int n = 0;
    char linha[256];

    do {
        printf("Introduza o ID do departamento a desativar: ");
        scanf("%d", &id);
        if (id < 0) printf("ID inválido!\n");
    } while (id < 0);

    // Ler departamentos do ficheiro
    while (fgets(linha, sizeof(linha), f)) {
        int idDept, ordens, estadoInt;
        float custo;
        char nome[50], resp[50], email[50], tel[50];

        if (sscanf(linha, " %d ; %49[^;] ; %49[^;] ; %49[^;] ; %19[^;] ; %d ; %f ; %d ;",
                   &idDept, nome, resp, email, tel, &ordens, &custo, &estadoInt) == 8) {
            lista[n].IdDept = idDept;
            strcpy(lista[n].nome, nome);
            strcpy(lista[n].responsavel, resp);
            strcpy(lista[n].email, email);
            strcpy(lista[n].telefone, tel);
            lista[n].ordens = ordens;
            lista[n].CustoTotal = custo;
            lista[n].estado = (EstadoDepartamento)estadoInt;
            n++;
        }
    }
    fclose(f);

    // Procurar departamento e atualizar
    int encontrado = 0;
    int estadoAntigo;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdDept == id) {
            estadoAntigo = lista[i].estado;
            lista[i].estado = Desativado;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Departamento com ID %d não encontrado.\n", id);
        return;
    }

    // Log
    char log[200];
    sprintf(log, "Departamento atualizado | ID: %d | Estado antigo: %d | Estado novo: %d",
            id, (EstadoDepartamento)estadoAntigo, Desativado);
    RegistarLog(log);

    // Reescrever ficheiro
    f = fopen("..\\Dados\\departamentos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
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

    // Solicitar ID ao utilizador
    do {
        printf("Introduza o ID do departamento a Reativar: ");
        scanf("%d", &id);
        if (id < 0) {
            printf("ID inválido!\n");
        }
    } while (id < 0);

    // Ler todos os departamentos do ficheiro
    while (fgets(linha, sizeof(linha), f)) {
        int estadoInt;
        if (sscanf(
                linha,
                "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%f;%d;",
                &lista[n].IdDept,
                lista[n].nome,
                lista[n].responsavel,
                lista[n].email,
                lista[n].telefone,
                &lista[n].ordens,
                &lista[n].CustoTotal,
                &estadoInt
            ) == 8) {
            lista[n].estado = (EstadoDepartamento)estadoInt; // converte int para enum
            n++;
        }
    }
    fclose(f);

    // Procurar departamento e reativar
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdDept == id) {
            if (lista[i].estado == ATIVO) {
                printf("O departamento já se encontra ativo.\n");
                return;
            }
            lista[i].estado = ATIVO;
            encontrado = 1;

            // Log
            char log[200];
            sprintf(log, "Departamento Reativado | ID: %d", id);
            RegistarLog(log);

            break;
        }
    }

    if (!encontrado) {
        printf("Departamento com ID %d não encontrado.\n", id);
        return;
    }

    // Escrever todos os departamentos de volta ao ficheiro
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
            lista[i].estado // enum como int
        );
    }
    fclose(f);

    printf("Departamento com ID %d reativado com sucesso.\n", id);
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

    // Logs
    char log[200];
    sprintf(log, "Ordem Adicionada ao Departamento | ID: %d ",id);
    RegistarLog(log);

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

    // Logs
    char log[200];
    sprintf(log, "Custo da ordem Adicionado ao Departamento | ID: %d |Custo: %f € ",idDept, valor);
    RegistarLog(log);

    // Substitui o ficheiro antigo pelo novo
    remove("../Dados/departamentos.txt");
    rename("../Dados/departamentos_tmp.txt", "../Dados/departamentos.txt");
}
