/**
 * @file ordens.cpp
 * @author Grupo 37
 * @date 27-12-2025
 * @version 1
 *
 * @brief Funções gerais do módulo "ordens".
 *
 * Este ficheiro contém as funções responsáveis pela gestão de ordens de manutenção,
 * incluindo criação de novas ordens, aceitação/início de trabalhos e atualização
 * dos estados associados.
 */

#include "ordens.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "../extra.h"
#include "../Ler/Ordens/leitura_ordens.h"
#include "../Menus/Menus Gerais/menus.h"
#include "../data/structs.h"
#include "../Menus/Menus Ordens/menu_ordens.h"
#include "../Equipamentos/Equipamentos.h"
#include "../Ler/Equipamentos/leitura_equipamentos.h"
#include "../Ler/Departamentos/leitura_departamentos.h"
#include "../Ler/Tecnicos/leitura_tecnicos.h"

OrdemDeManutencao CriarOrdemDeManutencao() {
    OrdemDeManutencao m;
    m.IdOrdem = ProximoIdManutencao(); // Gera o próximo ID disponível
    m.IdOrdem = -1; // Assume erro inicial

    printf("\n----- Menu de Criação de Ordens de Manutenção -----\n");

    ListarAtivos();
    printf("\nId do Ativo a ser reparado: ");
    while (scanf("%d", &m.IdAtivo) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n'); // Limpa buffer
        printf("Id do Ativo a ser reparado: ");
    }

    // Atualiza o estado do ativo
    if (!AtualizarEstadoAtivo(m.IdAtivo, EmReparacao)) {
        printf("Não foi possível atualizar o estado do ativo.\n");
        return m;
    }

    ListarDepartamentos();
    printf("\nId do Departamento requisitante: ");
    while (scanf("%d", &m.IdDepartamento) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n'); // Limpa buffer
        printf("Id do Departamento requisitante: ");
    }

    ObterDataAtual(m.DataPedido);

    m.estado = MenuEstadoOrdens();
    m.prioridade = MenuPrioridadeOrdens();

    // Validação do custo
    do {
        printf("\nCusto Estimado para a manutenção: ");
        if (scanf("%f", &m.custo) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n'); // Limpa buffer
            m.custo = -1; // força repetição
        }
    } while (m.custo < 0);

    // Mostra resumo da ordem criada
    printf("\nOrdem Criada!\n");
    printf("ID da Ordem: %d | Id do ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Prioridade: %s | Custo: %.2f€\n",
           m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
           EstadoManutencaoToStr(m.estado), PrioridadeManutencaoToStr(m.prioridade), m.custo);

    // --- Gravação no ficheiro ---
    FILE *f = fopen("../Dados/ordens.txt", "a");
    if (f == NULL) {
        perror("Erro ao abrir ficheiro");
        return m;
    }

    fprintf(f, "%d;%d;%d;%s;%s;%s;%.2f;\n",
            m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
            EstadoManutencaoToStr(m.estado), PrioridadeManutencaoToStr(m.prioridade), m.custo);

    fclose(f);

    return m; // Ordem criada com sucesso
}



// Função usada pelos técnicos para iniciar ordens pendentes
void IniciarTrabalho() {

    OrdemDeManutencao ordem;

    ListarOrdens();                      // Mostra todas as ordens para facilitar a escolha

    int idEscolhido;
    printf("\nId da ordem que deseja iniciar: ");
    scanf("%d", &idEscolhido);

    /* ================= LEITURA E ATUALIZAÇÃO DA ORDEM ================= */

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");   // Abre o ficheiro para leitura
    if (!f) {
        perror("Erro ao abrir ordens.txt");
        return;
    }

    char linhas[200][256];               // Armazena temporariamente todas as linhas do ficheiro
    int total = 0;
    int encontrada = 0;

    // Lê todas as linhas e procura a ordem correspondente
    while (fgets(linhas[total], sizeof(linhas[total]), f)) {

        int id;
        sscanf(linhas[total], "%d;%*199[^\n]", &id); // Extrai apenas o ID da ordem

        if (id == idEscolhido) {         // Ordem encontrada
            int idAtivo, idDept;
            char data[12], estado[20], prioridade[20];
            float custo;

            // Extrai todos os campos da linha
            sscanf(linhas[total],
                   "%d;%d;%d;%11[^;];%19[^;];%19[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, &custo);

            // Atualiza o estado para "Decorrer", preservando prioridade
            if (strlen(prioridade) == 0) {
                sprintf(linhas[total],
                        "%d;%d;%d;%s;Decorrer;;%.2f;\n",
                        id, idAtivo, idDept, data, custo);
            } else {
                sprintf(linhas[total],
                        "%d;%d;%d;%s;Decorrer;%s;%.2f;\n",
                        id, idAtivo, idDept, data, prioridade, custo);
            }

            encontrada = 1;
        }

        total++;
    }
    fclose(f);

    if (!encontrada) {
        printf("\nOrdem não encontrada!\n");
        return;
    }

    // Reescreve o ficheiro com a ordem atualizada
    f = fopen("..\\Dados\\ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhas[i], f);
    fclose(f);

    printf("\nOrdem %d iniciada com sucesso!\n", idEscolhido);

    /* ================= ASSOCIAÇÃO DE TÉCNICOS ================= */

    ListarTecnicos();                    // Lista técnicos disponíveis

    int qntd;
    printf("Quantos técnicos deseja associar (máx 10)? ");
    scanf("%d", &qntd);
    if (qntd > 10) qntd = 10;

    // Lê os IDs dos técnicos selecionados
    for (int i = 0; i < qntd; i++) {
        printf("Id do técnico %d: ", i + 1);
        scanf("%d", &ordem.idsTecnicos[i]);
    }

    ordem.totalTecnicos = qntd;

    // Regista no ficheiro os técnicos associados à ordem
    escreverOrdemTecnicos(&ordem);

    /* ================= ATUALIZAÇÃO DO ESTADO DOS TÉCNICOS ================= */

    FILE *g = fopen("..\\Dados\\tecnicos.txt", "r");
    if (!g) {
        perror("Erro ao abrir tecnicos.txt");
        return;
    }

    char linhasTec[200][256];
    total = 0;

    // Lê todos os técnicos e atualiza os selecionados para "Ocupado"
    while (fgets(linhasTec[total], sizeof(linhasTec[total]), g)) {

        int id;
        char nome[50], sobrenome[50], esp[50], estado[50];

        sscanf(linhasTec[total],
               "%d;%49[^;];%49[^;];%49[^;];%49[^;\n]",
               &id, nome, sobrenome, esp, estado);

        if (tecnicoSelecionado(id, ordem.idsTecnicos, ordem.totalTecnicos)) {
            sprintf(linhasTec[total],
                    "%d;%s;%s;%s;Ocupado;\n",
                    id, nome, sobrenome, esp);
        }

        total++;
    }
    fclose(g);

    // Reescreve o ficheiro com os estados atualizados
    g = fopen("..\\Dados\\tecnicos.txt", "w");
    if (!g) {
        perror("Erro ao abrir tecnicos.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhasTec[i], g);
    fclose(g);

    printf("\nEstados dos técnicos atualizados com sucesso!");
    printf("\nTrabalho iniciado com sucesso!\n");
}


int tecnicoSelecionado(int id, int ids[], int qntd) {
    for (int i = 0; i < qntd; i++)
        if (ids[i] == id)
            return 1;
    return 0;
}

int ObterTecnicosOrdem(int idOrdem, int idsTec[]) {
    FILE *f = fopen("../Dados/ordem_tecnico.txt", "r");
    if (!f) {
        printf("Erro ao abrir ficheiro de técnicos da ordem.\n");
        return 0;
    }

    int total = 0;
    int idO, idT;
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d;%d", &idO, &idT) == 2) {
            if (idO == idOrdem) {
                idsTec[total++] = idT;
            }
        }
    }

    fclose(f);
    return total; // número de técnicos ligados à ordem
}


void EncerrarTrabalhos() {
    int idEscolhido;

    printf("\nQual o Id da ordem que deseja finalizar: ");
    scanf("%d", &idEscolhido);

    char linhas[200][256];
    int total = 0;
    int encontrada = 0;
    int idAtivoOrdem = -1;

    // =================== LE ORDENS ===================
    FILE *f = fopen("../Dados/ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ordens.txt");
        return;
    }

    while (fgets(linhas[total], sizeof(linhas[total]), f)) {
        int id;
        sscanf(linhas[total], "%d;%*199[^\n]", &id);

        if (id == idEscolhido) {
            int idAtivo, idDept;
            char data[12], estado[20], prioridade[20];
            float custo;

            sscanf(linhas[total],
                   "%d;%d;%d;%11[^;];%19[^;];%19[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, &custo);

            idAtivoOrdem = idAtivo;

            // Reescreve a linha com estado Concluido
            if (strlen(prioridade) == 0) {
                sprintf(linhas[total],
                        "%d;%d;%d;%s;Concluido;;%.2f;\n",
                        id, idAtivo, idDept, data, custo);
            } else {
                sprintf(linhas[total],
                        "%d;%d;%d;%s;Concluido;%s;%.2f;\n",
                        id, idAtivo, idDept, data, prioridade, custo);
            }

            encontrada = 1;
        }
        total++;
    }
    fclose(f);

    if (!encontrada) {
        printf("\nOrdem não encontrada!\n");
        return;
    }

    f = fopen("../Dados/ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhas[i], f);
    fclose(f);

    printf("\nOrdem %d encerrada com sucesso!\n", idEscolhido);

    // =================== LIBERTAR TECNICOS ===================
    int idsTec[10];
    int qntdTec = ObterTecnicosOrdem(idEscolhido, idsTec);

    FILE *g = fopen("../Dados/tecnicos.txt", "r");
    if (!g) {
        perror("Erro ao abrir tecnicos.txt");
        return;
    }

    char linhasTec[200][256];
    total = 0;

    while (fgets(linhasTec[total], sizeof(linhasTec[total]), g)) {
        int id;
        char nome[50], sobrenome[50], esp[50], estado[50];

        sscanf(linhasTec[total],
               "%d;%49[^;];%49[^;];%49[^;];%49[^;\n]",
               &id, nome, sobrenome, esp, estado);

        if (tecnicoSelecionado(id, idsTec, qntdTec)) {
            sprintf(linhasTec[total],
                    "%d;%s;%s;%s;Disponivel;\n",
                    id, nome, sobrenome, esp);
        }
        total++;
    }
    fclose(g);

    g = fopen("../Dados/tecnicos.txt", "w");
    if (!g) {
        perror("Erro ao abrir tecnicos.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhasTec[i], g);
    fclose(g);

    printf("Estados dos técnicos atualizados para Disponível.\n");

    // =================== ATUALIZAR ESTADO DO ATIVO ===================
    if (idAtivoOrdem != -1) {
        int sucesso = AtualizarEstadoAtivo(idAtivoOrdem, EmOperacao);
        if (sucesso) {
            printf("Estado do ativo %d atualizado para Disponível.\n", idAtivoOrdem);
        } else {
            printf("Falha ao atualizar o estado do ativo %d.\n", idAtivoOrdem);
        }
    }
}

void escreverOrdemTecnicos(const OrdemDeManutencao *ordem) {
    FILE *f = fopen("..//..//ordem_tecnico.txt", "a"); // append
    if (!f) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    fprintf(f, "Ordem nº %d | Id Tecnicos: ", ordem->IdOrdem);

    for (int i = 0; i < ordem->totalTecnicos; i++) {
        fprintf(f, "%d;", ordem->idsTecnicos[i]);
    }

    fprintf(f, "\n");
    fclose(f);
}
