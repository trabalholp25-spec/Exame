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
    ObterDataAtual(dataFim); // obtém automaticamente a data de hoje

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


time_t ConverterData(const char *data) {
    int dia, mes, ano;
    sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano);

    struct tm tm_data = {0};
    tm_data.tm_mday = dia;
    tm_data.tm_mon = mes - 1;  // tm_mon é 0-11
    tm_data.tm_year = ano - 1900;

    return mktime(&tm_data);
}

// Função para comparar duas ordens pelo tempo (para qsort)
int CompararTempo(const void *a, const void *b) {
    OrdemDeManutencao *oa = (OrdemDeManutencao *)a;
    OrdemDeManutencao *ob = (OrdemDeManutencao *)b;

    if (oa->tempoDias < ob->tempoDias) return -1;
    else if (oa->tempoDias > ob->tempoDias) return 1;
    else return 0;
}

// Função principal para listar ordens por tempo de resolução
void ListarOrdensPorTempo() {
    FILE *f_ordens = fopen("../Dados/ordens.txt", "r");
    FILE *f_fim = fopen("../Dados/ordens_fim.txt", "r");

    if (!f_ordens || !f_fim) {
        printf("Erro ao abrir ficheiros.\n");
        if (f_ordens) fclose(f_ordens);
        if (f_fim) fclose(f_fim);
        return;
    }

    OrdemDeManutencao ordens[200];
    int total = 0;

    // Ler ordens.txt
    char linha[256];
    while (fgets(linha, sizeof(linha), f_ordens) && total < 200) {
        int id, idAtivo, idDept;
        char dataPedido[12];

        if (sscanf(linha, "%d;%d;%d;%11[^;];", &id, &idAtivo, &idDept, dataPedido) == 4) {
            ordens[total].IdOrdem = id;
            ordens[total].IdAtivo = idAtivo;
            ordens[total].IdDepartamento = idDept;
            strcpy(ordens[total].DataPedido, dataPedido);
            strcpy(ordens[total].DataFim, "00/00/0000"); // inicializa
            ordens[total].tempoDias = -1; // inicializa
            total++;
        }
    }
    fclose(f_ordens);

    // Ler ordens_fim.txt e associar DataFim
    while (fgets(linha, sizeof(linha), f_fim)) {
        int id;
        char dataFim[12];
        if (sscanf(linha, "%d;%11s", &id, dataFim) == 2) {
            // Procurar a ordem correspondente
            for (int i = 0; i < total; i++) {
                if (ordens[i].IdOrdem == id) {
                    strcpy(ordens[i].DataFim, dataFim);

                    // Calcular diferença em dias
                    time_t t_inicio = ConverterData(ordens[i].DataPedido);
                    time_t t_fim = ConverterData(ordens[i].DataFim);

                    double diff = difftime(t_fim, t_inicio) / (60*60*24);
                    ordens[i].tempoDias = (float)diff;
                    break;
                }
            }
        }
    }
    fclose(f_fim);

    // Ordenar por tempo (menor -> maior)
    qsort(ordens, total, sizeof(OrdemDeManutencao), CompararTempo);

    // Mostrar resultado
    printf("\nID Ordem | Ativo | Departamento | Data Pedido | Data Fim | Dias de Resolução\n");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        if (ordens[i].tempoDias >= 0) { // só mostrar ordens já concluídas
            printf("%7d | %5d | %11d | %11s | %9s | %6.0f\n",
                   ordens[i].IdOrdem,
                   ordens[i].IdAtivo,
                   ordens[i].IdDepartamento,
                   ordens[i].DataPedido,
                   ordens[i].DataFim,
                   ordens[i].tempoDias);
        }
    }
}