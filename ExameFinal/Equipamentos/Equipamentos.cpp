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
#include "../extra.h"
#include "../Menus/Menus Gerais/menus.h"
#include "../verificacoes.h"
#include "../data/structs.h"
#include "../Menus/Menus Equipamentos/menus_equipamentos.h"
#include "../Ler/Equipamentos/leitura_equipamentos.h"


Ativo CriarEquipamento() {
    Ativo a;
    a.reparos = 0;

    a.IdAtv = ProximoIdAtivo();  // Gerar o Id do Ativo

    printf ("\n----- Menu de Criação de Equipamentos -----");
    // Limpar buffer de fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nNome do Equipamento: ");  // Nome do Ativo
    fgets(a.nome, sizeof(a.nome), stdin);
    a.nome[strcspn(a.nome, "\n")] = 0;  // Remove o '\n' no final

    printf("\nLocalização: "); // Localização do Ativo
    fgets(a.localizacao, sizeof(a.localizacao), stdin);
    a.localizacao[strcspn(a.localizacao, "\n")] = 0;  // Remove o '\n' no final


    do {
        printf("\n Data de Aquisição (DD/MM/AAAA): "); // Data de Aquisição do Ativo
        scanf("%11s", a.data);

        if (!ValidarDataAquisicao(a.data)) // Chama a função "ValidarDataAquisicao" para verificar se a Data é realmente válida
            printf("Data inválida. Tente novamente.\n");

    } while (!ValidarDataAquisicao(a.data)); // Loop enquanto a data não for válida

    a.categoria = MenuCategoria(); // Menu para escolher a categoria

    a.estado = MenuEstadoAtivos(); // Menu para escolher o estado do Ativo

    printf ("\nAtivo Criado!"); // Confirmação da criação do ativo
    printf("\nID: %d | Nome: %s | Localização: %s | Data de aquisição: %s | Categoria: %s | Estado: %s | Reparações: %d",a.IdAtv, a.nome, a.localizacao, a.data, CategoriaToStr(a.categoria), EstadoAtivoToStr(a.estado), a.reparos);

    // --- Gravar no ficheiro ---
    FILE *f = fopen("..\\Dados\\ativos.txt", "a");
    if (f == NULL) {
        perror("Erro ao abrir ficheiro");
        exit(1);
    }

    fprintf(f, "%d;%s;%s;%s;%s;%s;%d;\n", a.IdAtv,a.nome, a.localizacao, a.data, CategoriaToStr(a.categoria), EstadoAtivoToStr(a.estado),a.reparos);

    fclose(f);
    // --------------------------

    return a;
}

void EliminarAtivos() {
    // Abrir o Ficheiro ativos.txt
    FILE *f = fopen("..\\Dados\\ativos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    printf("Introduza o ID do ativo a eliminar: "); // Id do ativo que o utilizador deseja eliminar
    scanf("%d", &id);

    Ativo lista[100];
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
                  lista[n].reparos) == 7) {

        lista[n].categoria = StrToCategoria(bufferCat);
        lista[n].estado = StrToEstadoAtivo(bufferEst);
        n++;
                  }

    fclose(f);

    // Procurar e marcar como INATIVO
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdAtv == id) {
            lista[i].estado = Inativo;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) { // Caso o Ativo não seja encomntrado
        printf("Ativo com ID %d não encontrado.\n", id);
        return;
    }

    // Reescrever o ficheiro
    f = fopen("..\\Dados\\ativos.txt", "w");
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

int AtualizarEstadoAtivo(int idAtivo, EstadoEquipamento novoEstado) {
    // Abrir o ficheiro .txt no modo "r"(read)
    FILE *f = fopen("../Dados/ativos.txt", "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro de ativos.\n");
        return 0;
    }

    // Declaração de variáveis
    Ativo ativos[200];
    int total = 0;
    int encontrado = 0;
    char linha[256];
    char bufferCat[50], bufferEst[50];

    // lê o ficheiro .txt
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha,
                   "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;",
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

    fclose(f); // Fecha o .txt

    // Mudar o estado do Ativo
    for (int i = 0; i < total; i++) {
        if (ativos[i].IdAtv == idAtivo) {

            // Impede mudança se já estiver em reparação
            if (ativos[i].estado == EmReparacao) {
                printf("O ativo já se encontra em reparação.\n");
                return 0;
            }

            ativos[i].estado = novoEstado;
            encontrado = 1;
            break;
        }
    }

    // Caso o ativo não seja encontrado
    if (!encontrado) {
        printf("Ativo não encontrado.\n");
        return 0;
    }

    // Reescrever o ficheiro com o estado atualizado
    f = fopen("../Dados/ativos.txt", "w");
    if (!f) {
        printf("Erro ao reabrir o ficheiro de ativos.\n");
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

    printf("Estado do ativo atualizado para Em Reparação.\n");
    return 1;
}

