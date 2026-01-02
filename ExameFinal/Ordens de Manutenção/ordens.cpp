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
#include "../Tecnicos/tecnico.h"

OrdemDeManutencao CriarOrdemDeManutencao() {
    OrdemDeManutencao m;
    m.IdOrdem = ProximoIdManutencao(); // Gera o próximo ID disponível

    printf("\n----- Menu de Criação de Ordens de Manutenção -----\n");

    ListarAtivos();
    printf("\nId do Ativo a ser reparado: ");
    while (scanf(" %d", &m.IdAtivo) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n');
        printf("Id do Ativo a ser reparado: ");
    }
    getchar(); // limpar \n residual

    if (!AtualizarEstadoAtivo(m.IdAtivo, EmReparacao)) {
        printf("Não foi possível atualizar o estado do ativo.\n");
        return m;
    }

    ListarDepartamentos();
    printf("\nId do Departamento requisitante: ");
    while (scanf("%d", &m.IdDepartamento) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n');
        printf("Id do Departamento requisitante: ");
    }
    getchar();

    ObterDataAtual(m.DataPedido);

    m.estado = MenuEstadoOrdens();
    m.prioridade = MenuPrioridadeOrdens();
    m.tipo = MenuTipoOrdens();

    // Validação do custo
    do {
        printf("\nCusto Estimado para a manutenção: ");
        if (scanf("%f", &m.custo) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n');
            m.custo = -1;
        }
    } while (m.custo < 0);
    getchar();

    printf("\nOrdem Criada!\n");
    printf("ID da Ordem: %d | Id do ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Prioridade: %s | Tipo: %s| Custo: %.2f€\n",
           m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
           EstadoManutencaoToStr(m.estado),PrioridadeManutencaoToStr(m.prioridade), TipoManutencaoToStr(m.tipo), m.custo);

    // --- Gravação no ficheiro ---
    FILE *f = fopen("../Dados/ordens.txt", "a");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return m;
    }

    // Linha segura
    char linha[512];
    snprintf(linha, sizeof(linha), "%d;%d;%d;%s;%s;%s;%s;%.2f;\n",
             m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
             EstadoManutencaoToStr(m.estado),PrioridadeManutencaoToStr(m.prioridade), TipoManutencaoToStr(m.tipo), m.custo);

    fputs(linha, f);
    fclose(f);

    return m;
}


void IniciarTrabalho() {
    OrdemDeManutencao ordem = {0};
    int lista;

    lista = ListarOrdensNaoConcluidas();
    if (lista != 1) {
        printf ("\nNenhuma Ordem Pendente!!");
        return;
    }
    int idEscolhido;
    printf("\nId da ordem que deseja iniciar: ");
    scanf("%d", &idEscolhido);
    getchar();

    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ordens.txt");
        return;
    }

    char linhas[200][512];
    int total = 0;
    int encontrada = 0;

    while (fgets(linhas[total], sizeof(linhas[total]), f)) {
        int id;
        sscanf(linhas[total], "%d;%*511[^\n]", &id);

        if (id == idEscolhido) {
            int idAtivo, idDept;
            char data[50], estado[50], prioridade[50], tipo[50];
            float custo;

            sscanf(linhas[total], "%d;%d;%d;%49[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, tipo, &custo);

            if (strlen(prioridade) == 0) {
                snprintf(linhas[total], sizeof(linhas[total]),
                         "%d;%d;%d;%s;Decorrer;;%s;%.2f;\n",
                         id, idAtivo, idDept, data, tipo, custo);
            } else {
                snprintf(linhas[total], sizeof(linhas[total]),
                         "%d;%d;%d;%s;Decorrer;%s;%s;%.2f;\n",
                         id, idAtivo, idDept, data, prioridade, tipo, custo);
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

    f = fopen("..\\Dados\\ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhas[i], f);
    fclose(f);

    printf("\nOrdem %d iniciada com sucesso!\n", idEscolhido);


    // --- ASSOCIAR TÉCNICOS ---
    ListarTecnicos();

    int qntd;
    printf("Quantos técnicos deseja associar (máx 10)? ");
    if (scanf("%d", &qntd) != 1) {
        printf("Entrada inválida.\n");
        while(getchar() != '\n');
        return;
    }
    if (qntd > 10) qntd = 10;

    ordem.totalTecnicos = 0;

    while (ordem.totalTecnicos < qntd) {
        int idTec;
        int sucesso = 0;

        do {
            printf("\nLista de técnicos disponíveis:\n");
            ListarTecnicos();

            printf("Escolha o ID do técnico %d: ", ordem.totalTecnicos + 1);
            if (scanf("%d", &idTec) != 1) {
                printf("Entrada inválida.\n");
                while(getchar() != '\n');
                continue;
            }

            // Verifica duplicados
            int duplicado = 0;
            for (int j = 0; j < ordem.totalTecnicos; j++) {
                if (ordem.idsTecnicos[j] == idTec) {
                    duplicado = 1;
                    break;
                }
            }
            if (duplicado) {
                printf("Este técnico já foi associado. Escolha outro.\n");
                continue;
            }

            // Atualiza estado do técnico
            if (AtualizarEstadoTecnico(idTec, OCUPADO)) {
                ordem.idsTecnicos[ordem.totalTecnicos] = idTec;
                ordem.totalTecnicos++;
                sucesso = 1;
            } else {
                printf("Técnico inválido ou já se encontra OCUPADO. Escolha outro.\n");
            }

        } while (!sucesso);
    }

    // Escreve no ficheiro **uma única vez**
    EscreverTecnicosOrdem(idEscolhido, ordem.idsTecnicos, ordem.totalTecnicos);

    printf("\nEstados dos técnicos atualizados com sucesso!");
    printf("\nTrabalho iniciado com sucesso!\n");
}

int EscreverTecnicosOrdem(int idOrdem, int idsTec[], int totalTec) {
    FILE *f = fopen("../Dados/ordem_tecnico.txt", "a");
    if (!f) {
        printf("Erro ao abrir ficheiro de técnicos da ordem.\n");
        return 0;
    }

    fprintf(f, "Id da Ordem: %d | Id tecnicos associados:", idOrdem);
    for (int i = 0; i < totalTec; i++) {
        fprintf(f, " %d", idsTec[i]);
    }
    fprintf(f, "\n");

    fclose(f);
    return 1;
}


int ObterTecnicosOrdem(int idOrdem, int idsTec[]) {
    FILE *f = fopen("../Dados/ordem_tecnico.txt", "r");
    if (!f) {
        printf("Erro ao abrir ficheiro de técnicos da ordem.\n");
        return 0;
    }

    int total = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {
        int idO;
        // procura o padrão "Id da Ordem: <id> | Id tecnicos associados: "
        if (sscanf(linha, "Id da Ordem: %d |", &idO) == 1) {
            if (idO == idOrdem) {
                // agora extrair os IDs restantes da linha
                char *p = strchr(linha, ':'); // encontra o primeiro ':'
                if (p) {
                    p++; // move para o próximo caractere
                    // p aponta para " <id1> <id2> ... "
                    while (*p) {
                        int idTec;
                        if (sscanf(p, "%d", &idTec) == 1) {
                            idsTec[total++] = idTec;
                            // avançar até ao próximo número
                            while (*p && *p != ' ') p++;
                            while (*p && *p == ' ') p++;
                        } else {
                            break;
                        }
                    }
                }
                break; // encontrou a ordem, não precisa continuar
            }
        }
    }

    fclose(f);
    return total;
}



void EncerrarTrabalhos() {
    int idEscolhido;

    // --- Pedir ID da ordem ---
    printf("\nQual o Id da ordem que deseja finalizar: ");
    if (scanf("%d", &idEscolhido) != 1) {
        printf("Entrada inválida.\n");
        while(getchar() != '\n');
        return;
    }
    getchar(); // Limpa \n residual

    // --- Ler e atualizar ordens ---
    char linhas[200][256] = {{0}};
    int total = 0;
    int encontrada = 0;
    int idAtivoOrdem = -1;

    FILE *f = fopen("../Dados/ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ordens.txt");
        return;
    }

    while (fgets(linhas[total], sizeof(linhas[total]), f) && total < 200) {
        int id, idAtivo, idDept;
        char data[12], estado[20], prioridade[20], tipo[20];
        float custo;

        if (sscanf(linhas[total],
                   "%d;%d;%d;%11[^;];%19[^;];%19[^;];%19[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, tipo, &custo) == 8) {

            if (id == idEscolhido) {
                idAtivoOrdem = idAtivo;

                snprintf(linhas[total], sizeof(linhas[total]),
                         "%d;%d;%d;%s;Concluido;%s;%s;%.2f;\n",
                         id, idAtivo, idDept, data, prioridade, tipo, custo);

                encontrada = 1;
            }
        }
        total++;
    }
    fclose(f);

    if (!encontrada) {
        printf("\nOrdem não encontrada!\n");
        return;
    }

    // Reescrever ficheiro de ordens
    f = fopen("../Dados/ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++) {
        fputs(linhas[i], f);
    }
    fclose(f);

    printf("\nOrdem %d encerrada com sucesso!\n", idEscolhido);

    // --- Libertar técnicos ---
    int idsTec[10] = {0};
    int qntdTec = ObterTecnicosOrdem(idEscolhido, idsTec);

    for (int i = 0; i < qntdTec; i++) {
        if (AtualizarEstadoTecnico(idsTec[i], DISPONIVEL)) {
            printf("Técnico %d libertado.\n", idsTec[i]);
        } else {
            printf("Falha ao libertar técnico %d.\n", idsTec[i]);
        }
    }

    if (qntdTec > 0)
        printf("Todos os técnicos ligados à ordem foram libertados.\n");

    // --- Atualizar ativo ---
    if (idAtivoOrdem != -1) {
        if (AtualizarEstadoAtivo(idAtivoOrdem, EmOperacao)) {
            AdicionarReparo(idAtivoOrdem);
            printf("Ativo %d atualizado para Disponível e reparos incrementados.\n", idAtivoOrdem);
        } else {
            printf("Falha ao atualizar ativo %d.\n", idAtivoOrdem);
        }
    }
}

