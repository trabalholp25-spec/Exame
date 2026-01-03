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

// --- Criar um novo Ativo/Equipamento ---
Ativo CriarEquipamento() {
    Ativo a;
    a.reparos = 0;

    a.IdAtv = ProximoIdAtivo();  // Gerar o Id do Ativo

    printf("\n----- Menu de Criação de Equipamentos -----\n");

    // Limpar buffer antes de fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Nome do Equipamento: ");
    fgets(a.nome, sizeof(a.nome), stdin);
    a.nome[strcspn(a.nome, "\n")] = 0;  // Remove '\n'

    printf("Localização: ");
    fgets(a.localizacao, sizeof(a.localizacao), stdin);
    a.localizacao[strcspn(a.localizacao, "\n")] = 0;

    // Data de aquisição válida
    do {
        printf("Data de Aquisição (DD/MM/AAAA): ");
        scanf("%11s", a.data);
        if (!ValidarDataAquisicao(a.data))
            printf("Data inválida. Tente novamente.\n");
    } while (!ValidarDataAquisicao(a.data));

    a.categoria = MenuCategoria();       // Escolha de categoria
    a.estado = MenuEstadoAtivos();       // Escolha de estado

    // Mostrar resumo do ativo
    printf("\nAtivo Criado!\n");
    printf("ID: %d | Nome: %s | Localização: %s | Data: %s | Categoria: %s | Estado: %s | Reparos: %d\n",
           a.IdAtv, a.nome, a.localizacao, a.data,
           CategoriaToStr(a.categoria),
           EstadoAtivoToStr(a.estado),
           a.reparos);

    // Gravar no ficheiro
    FILE *f = fopen("../Dados/ativos.txt", "a");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        exit(1);
    }
    fprintf(f, "%d;%s;%s;%s;%s;%s;%d;\n",
            a.IdAtv, a.nome, a.localizacao, a.data,
            CategoriaToStr(a.categoria),
            EstadoAtivoToStr(a.estado),
            a.reparos);
    fclose(f);

    return a;
}

// --- Eliminar/Marcar ativo como Inativo ---
void EliminarAtivos() {
    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    printf("Introduza o ID do ativo a eliminar: ");
    scanf("%d", &id);

    Ativo lista[200];
    int n = 0;
    char bufferCat[50], bufferEst[50];

    // Ler todos os ativos
    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                  &lista[n].IdAtv,
                  lista[n].nome,
                  lista[n].localizacao,
                  lista[n].data,
                  bufferCat,
                  bufferEst,
                  &lista[n].reparos) == 7) {
        lista[n].categoria = StrToCategoria(bufferCat);
        lista[n].estado = StrToEstadoAtivo(bufferEst);
        n++;
    }
    fclose(f);

    // Procurar o ativo e marcar como Inativo
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdAtv == id) {
            lista[i].estado = Inativo;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Ativo com ID %d não encontrado.\n", id);
        return;
    }

    // Reescrever ficheiro
    f = fopen("../Dados/ativos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;\n",
                lista[i].IdAtv,
                lista[i].nome,
                lista[i].localizacao,
                lista[i].data,
                CategoriaToStr(lista[i].categoria),
                EstadoAtivoToStr(lista[i].estado),
                lista[i].reparos);
    }
    fclose(f);

    printf("Ativo com ID %d marcado como Inativo.\n", id);
}

// --- Atualizar o estado de um ativo específico ---
int AtualizarEstadoAtivo(int idAtivo, EstadoEquipamento novoEstado) {
    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro de ativos");
        return 0;
    }

    Ativo ativos[200];
    int total = 0;
    int encontrado = 0;
    char linha[256];
    char bufferCat[50], bufferEst[50];

    // Ler todos os ativos
    while (fgets(linha, sizeof(linha), f) && total < 200) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                   &ativos[total].IdAtv,
                   ativos[total].nome,
                   ativos[total].localizacao,
                   ativos[total].data,
                   bufferCat,
                   bufferEst,
                   &ativos[total].reparos) == 7) {
            ativos[total].categoria = StrToCategoria(bufferCat);
            ativos[total].estado = StrToEstadoAtivo(bufferEst);
            total++;
        }
    }
    fclose(f);

    // Atualizar estado
    for (int i = 0; i < total; i++) {
        if (ativos[i].IdAtv == idAtivo) {
            // Impede mudança redundante para EmReparacao
            if (ativos[i].estado == EmReparacao && novoEstado == EmReparacao) {
                printf("O ativo já se encontra em reparação.\n");
                return 0;
            }
            ativos[i].estado = novoEstado;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Ativo não encontrado.\n");
        return 0;
    }

    // Reescrever ficheiro com novos estados
    f = fopen("../Dados/ativos.txt", "w");
    if (!f) {
        perror("Erro ao reabrir ficheiro de ativos");
        return 0;
    }
    for (int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;\n",
                ativos[i].IdAtv,
                ativos[i].nome,
                ativos[i].localizacao,
                ativos[i].data,
                CategoriaToStr(ativos[i].categoria),
                EstadoAtivoToStr(ativos[i].estado),
                ativos[i].reparos);
    }
    fclose(f);

    printf("Estado do ativo %d atualizado para %s.\n", idAtivo, EstadoAtivoToStr(novoEstado));
    return 1;
}

// --- Incrementa o contador de reparos de um ativo ---
void AdicionarReparo(int Id) {
    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        perror("Erro ao abrir ficheiro de ativos");
        return;
    }

    Ativo ativos[200];
    int total = 0;
    int encontrado = 0;
    char linha[256];
    char bufferCat[50], bufferEst[50];

    // Ler todos os ativos
    while (fgets(linha, sizeof(linha), f) && total < 200) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
                   &ativos[total].IdAtv,
                   ativos[total].nome,
                   ativos[total].localizacao,
                   ativos[total].data,
                   bufferCat,
                   bufferEst,
                   &ativos[total].reparos) == 7) {
            ativos[total].categoria = StrToCategoria(bufferCat);
            ativos[total].estado = StrToEstadoAtivo(bufferEst);

            if (ativos[total].IdAtv == Id) {
                ativos[total].reparos++;
                encontrado = 1;
            }

            total++;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Ativo %d não encontrado.\n", Id);
        return;
    }

    // Reescrever ficheiro atualizado
    f = fopen("../Dados/ativos.txt", "w");
    if (!f) {
        perror("Erro ao reabrir ficheiro de ativos");
        return;
    }
    for (int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;\n",
                ativos[i].IdAtv,
                ativos[i].nome,
                ativos[i].localizacao,
                ativos[i].data,
                CategoriaToStr(ativos[i].categoria),
                EstadoAtivoToStr(ativos[i].estado),
                ativos[i].reparos);
    }
    fclose(f);

    printf("Reparo adicionado ao ativo %d.\n", Id);
}

