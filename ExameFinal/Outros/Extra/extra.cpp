/**
* @file extra.cpp
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de funções extras;
 *
 * Este ficheiro contém as funções utilizadas para gerir todo o tipo de Ids,
 * limpeza do buffer e obter a data atual.
 */


#include "extra.h"

#include <cstdlib>
#include <cstring>
#include <time.h>
#include <stdio.h>

#include "../../data/structs.h"

// --- Limpa o buffer de entrada do teclado (stdin) ---
// Útil após ler números com scanf antes de usar fgets para strings,
// para evitar que restos de '\n' interfiram na leitura.
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // descarta todos os caracteres até encontrar '\n' ou EOF
    }
}

// --- Retorna o próximo ID disponível para técnicos ---
// Lê o ficheiro "tecnicos.txt", encontra o maior ID e devolve +1.
// Se o ficheiro não existir, começa em 1.
int ProximoIdTecnico() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (!f) return 1; // ficheiro não existe

    int maxId = 0;
    int id;
    char nome[50], esp[50], est[50];

    // Lê todas as linhas, extrai o ID e mantém o máximo
    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^;];", &id, nome, esp, est) == 4) {
        if (id > maxId)
            maxId = id;
    }

    fclose(f);
    return maxId + 1; // próximo ID disponível
}

// --- Retorna o próximo ID disponível para ativos ---
// Lê "ativos.txt" e calcula o próximo ID único.
int ProximoIdAtivo() {
    FILE *f = fopen("..\\Dados\\ativos.txt", "r");
    if (!f) return 1;

    int maxId = 0;
    int id;
    char nome[50], loc[50], data[50], cat[50], est[50];

    // Lê linhas no formato: id;nome;localizacao;data;categoria;estado;
    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;\n]\n",
                  &id, nome, loc, data, cat, est) == 6)
    {
        if (id > maxId)
            maxId = id;
    }

    fclose(f);
    return maxId + 1;
}

// --- Retorna o próximo ID disponível para departamentos ---
// Lê "departamentos.txt" e devolve o próximo ID.
int ProximoIdDept() {
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) return 1;

    int maxId = 0;
    int id, ordens, estado;
    char nome[50], resp[50], email[50], telf[50];
    float custo;

    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%d;%f;%d;\n",
                  &id, nome, resp, email, telf, &ordens, &custo, &estado) == 8)
    {
        if (id > maxId)
            maxId = id;
    }

    fclose(f);
    return maxId + 1;
}

// --- Retorna o próximo ID disponível para ordens de manutenção ---
// Lê "ordens.txt" e encontra o maior ID.
int ProximoIdManutencao() {
    FILE *f = fopen("../Dados/ordens.txt", "r");
    if (!f) return 1;

    int maxId = 0;
    int id;
    char buffer[256]; // descarta resto da linha

    while (fgets(buffer, sizeof(buffer), f)) {
        if (sscanf(buffer, "%d;", &id) == 1) {
            if (id > maxId)
                maxId = id;
        }
    }

    fclose(f);
    return maxId + 1;
}

// --- Obtém a data atual no formato DD/MM/AAAA ---
// Preenche o array 'data' fornecido.
void ObterDataAtual(char data[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(data, "%02d/%02d/%04d",
            tm.tm_mday,      // dia
            tm.tm_mon + 1,   // mês (0-11, por isso +1)
            tm.tm_year + 1900); // ano
}


void GravarDataConclusao(int idOrdem) {

    char dataFim[12];

    ObterDataAtual(dataFim);

    FILE *f = fopen("../Dados/ordens_fim.txt", "a"); // abre em append
    if (!f) {
        perror("Erro ao abrir ficheiro de datas finais");
        return;
    }

    // Escreve: IdOrdem;DataFim;
    fprintf(f, "%d;%s;\n", idOrdem, dataFim);
    fclose(f);

    printf("Data de conclusão gravada para a ordem %d: %s\n", idOrdem, dataFim);
}

void ListarTempoOrdens(int idOrdem) {

    int id;
    char dataFim[12] = "";

    FILE *fFim = fopen("../Dados/ordens_fim.txt", "r");
    if (!fFim) {
        perror("Erro ao abrir ficheiro de datas finais");
        return;
    }

    while (fscanf(fFim, "%d;%11[^;];\n", &id, dataFim) == 2) {
        if (id == idOrdem) {
            break;
        }
    }
    fclose(fFim);


    int idAtivo, idDept, estado;
    char dataInicio[12] = "";
    char prioridade[50], tipo[50];
    float custo;

    FILE *fInicio = fopen("../Dados/ordens.txt", "r");
    if (!fInicio) {
        perror("Erro ao abrir ficheiro de ordens");
        return;
    }

    while (fscanf(fInicio,
           "%d;%d;%d;%11[^;];%d;%49[^;];%49[^;];%f;\n",
           &id, &idAtivo, &idDept, dataInicio,
           &estado, prioridade, tipo, &custo) == 8) {

        if (id == idOrdem) {
            break;
        }
           }
    fclose(fInicio);

    int tempoDias = 0;

    if (strlen(dataInicio) > 0 && strlen(dataFim) > 0) {

        struct tm tInicio = {0}, tFim = {0};

        sscanf(dataInicio, "%d/%d/%d",
               &tInicio.tm_mday,
               &tInicio.tm_mon,
               &tInicio.tm_year);

        sscanf(dataFim, "%d/%d/%d",
               &tFim.tm_mday,
               &tFim.tm_mon,
               &tFim.tm_year);

        tInicio.tm_mon -= 1;
        tFim.tm_mon -= 1;
        tInicio.tm_year -= 1900;
        tFim.tm_year -= 1900;

        time_t inicio = mktime(&tInicio);
        time_t fim = mktime(&tFim);

        tempoDias = (int)((fim - inicio) / (60 * 60 * 24));
    }

    FILE *fTempo = fopen("../Dados/tempo_ordem.txt", "a");
    if (fTempo) {
        fprintf(fTempo, "%d;%d\n", idOrdem, tempoDias);
        fclose(fTempo);
    }
}
void ListarOrdensPorTempo() {

    FILE *fTempo = fopen("../Dados/tempo_ordem.txt", "r");

    if (!fTempo) {
        perror("Erro ao abrir ficheiro de ordens");
        return;
    }

    int idOrdem;
    int dias;
    int ordens = 0;
    int diastotal = 0;

    printf("Ordens por tempo:\n");

    while (fscanf(fTempo, "%d;%d", &idOrdem, &dias) == 2) {
        printf("ID da Ordem: %d | Tempo de resolução: %d dias!\n", idOrdem, dias);
        ordens++;
        diastotal += dias;
    }

    printf ("----------------------\n");

    if (ordens > 0) {
        int media = diastotal / ordens;
        printf("Média de DIAS para resolução de problemas: %d dias!\n", media);
    } else {
        printf("Não existem ordens registadas.\n");
    }

    fclose(fTempo);
}