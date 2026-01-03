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
#include "../Outros/Extra/extra.h"
#include "../Departamentos/departamentos.h"
#include "../Listagem/Ordens/leitura_ordens.h"
#include "../Menus/Menus Gerais/menus.h"
#include "../data/structs.h"
#include "../Menus/Menus Ordens/menu_ordens.h"
#include "../Equipamentos/Equipamentos.h"
#include "../Listagem/Equipamentos/leitura_equipamentos.h"
#include "../Listagem/Departamentos/leitura_departamentos.h"
#include "../Listagem/Tecnicos/leitura_tecnicos.h"
#include "../Tecnicos/tecnico.h"

// --- Criação de uma nova ordem de manutenção ---
OrdemDeManutencao CriarOrdemDeManutencao() {
    OrdemDeManutencao m;

    // Gerar o próximo ID disponível
    m.IdOrdem = ProximoIdManutencao();

    printf("\n----- Menu de Criação de Ordens de Manutenção -----\n");

    // Listar todos os ativos disponíveis para que o utilizador escolha
    ListarAtivos();
    printf("\nId do Ativo a ser reparado: ");

    // Validação de entrada do ID do ativo
    while (scanf(" %d", &m.IdAtivo) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n')  // Limpa buffer
            printf("Id do Ativo a ser reparado: ");
    }
    getchar(); // Limpa o '\n' residual

    // Atualiza o estado do ativo para "EmReparacao"
    if (!AtualizarEstadoAtivo(m.IdAtivo, EmReparacao)) {
        printf("Não foi possível atualizar o estado do ativo.\n");
        return m; // retorna a ordem incompleta
    }

    // Listar departamentos ativos e escolher o requisitante
    Departamento* dep = nullptr;
    ListarDepartamentos();
    printf("\nId do Departamento requisitante: ");
    while (scanf("%d", &m.IdDepartamento) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n'); // Limpa buffer
        printf("Id do Departamento requisitante: ");
    }

    // Incrementa o número de ordens no departamento escolhido
    AdicionarOrdem(m.IdDepartamento);

    // Obter a data atual para a ordem
    ObterDataAtual(m.DataPedido);

    // Escolha de estado, prioridade e tipo através de menus
    m.estado = MenuEstadoOrdens();
    m.prioridade = MenuPrioridadeOrdens();
    m.tipo = MenuTipoOrdens();

    // Registro do custo da manutenção
    printf("\n----- Registo de Materiais -----");
    getchar(); // Limpa buffer
    m.custo = RegistarMateriaisOrdem(m.IdOrdem);

    // Adiciona custo ao departamento
    AdicionarCustoDepartamento(m.IdDepartamento, m.custo);
    getchar(); // Limpa '\n'

    // Mostrar resumo da ordem criada
    printf("\nOrdem Criada!\n");
    printf("ID da Ordem: %d | Id do ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Prioridade: %s | Tipo: %s| Custo: %.2f€\n",
           m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
           EstadoManutencaoToStr(m.estado),
           PrioridadeManutencaoToStr(m.prioridade),
           TipoManutencaoToStr(m.tipo),
           m.custo);

    // --- Gravação da ordem no ficheiro ---
    FILE *f = fopen("../Dados/ordens.txt", "a"); // Append no ficheiro
    if (!f) {
        perror("Erro ao abrir ficheiro");
    }

    // Linha formatada para o ficheiro
    char linha[512];
    snprintf(linha, sizeof(linha), "%d;%d;%d;%s;%s;%s;%s;%.2f;\n",
             m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
             EstadoManutencaoToStr(m.estado),
             PrioridadeManutencaoToStr(m.prioridade),
             TipoManutencaoToStr(m.tipo),
             m.custo);

    fputs(linha, f);
    fclose(f);

    return m; // Retorna a ordem criada
}

// --- Iniciar um trabalho baseado numa ordem pendente ---
void IniciarTrabalho() {
    OrdemDeManutencao ordem = {0};
    int lista;

    // Lista ordens que ainda não foram concluídas
    lista = ListarOrdensNaoConcluidas();
    if (lista != 1) {
        printf ("\nNenhuma Ordem Pendente!!");
        return;
    }

    int idEscolhido;
    printf("\nId da ordem que deseja iniciar: ");
    scanf("%d", &idEscolhido);
    getchar(); // Limpa buffer

    // Lê todas as ordens do ficheiro para localizar a escolhida
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
        sscanf(linhas[total], "%d;%*511[^\n]", &id); // Lê apenas o ID

        if (id == idEscolhido) {
            int idAtivo, idDept;
            char data[50], estado[50], prioridade[50], tipo[50];
            float custo;

            sscanf(linhas[total], "%d;%d;%d;%49[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, tipo, &custo);

            // Atualiza o estado da ordem para "Decorrer"
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

    // Reescreve todas as ordens no ficheiro com a atualização
    f = fopen("..\\Dados\\ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhas[i], f);
    fclose(f);

    printf("\nOrdem %d iniciada com sucesso!\n", idEscolhido);

    // --- Associar técnicos ao trabalho ---
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

    // Loop de seleção de técnicos disponíveis
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

            // Verifica duplicados na mesma ordem
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

            // Atualiza o estado do técnico para OCUPADO
            if (AtualizarEstadoTecnico(idTec, OCUPADO)) {
                ordem.idsTecnicos[ordem.totalTecnicos] = idTec;
                ordem.totalTecnicos++;
                sucesso = 1;
            } else {
                printf("Técnico inválido ou já se encontra OCUPADO. Escolha outro.\n");
            }

        } while (!sucesso);
    }

    // Escreve no ficheiro de técnicos da ordem
    EscreverTecnicosOrdem(idEscolhido, ordem.idsTecnicos, ordem.totalTecnicos);

    printf("\nEstados dos técnicos atualizados com sucesso!");
    printf("\nTrabalho iniciado com sucesso!\n");
}

// --- Escreve os IDs dos técnicos associados a uma ordem ---
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

// --- Lê os IDs dos técnicos associados a uma ordem ---
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
        // Procura o padrão "Id da Ordem: <id> |"
        if (sscanf(linha, "Id da Ordem: %d |", &idO) == 1) {
            if (idO == idOrdem) {
                // Extrai todos os IDs restantes da linha
                char *p = strchr(linha, ':');
                if (p) {
                    p++; // Move após ':'
                    while (*p) {
                        int idTec;
                        if (sscanf(p, "%d", &idTec) == 1) {
                            idsTec[total++] = idTec;
                            while (*p && *p != ' ') p++;
                            while (*p && *p == ' ') p++;
                        } else {
                            break;
                        }
                    }
                }
                break; // Ordem encontrada
            }
        }
    }

    fclose(f);
    return total; // Retorna quantidade de técnicos encontrados
}





