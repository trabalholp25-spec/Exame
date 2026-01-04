/**
 * @file ordens.cpp
 * @author Grupo 37
 * @date 27-12-2025
 * @version 1
 *
 * @brief Funções gerais do módulo "ordens".
 *
 * Este ficheiro contém funções para gestão de ordens de manutenção, incluindo:
 * - Criação de ordens
 * - Início de trabalhos
 * - Encerramento de ordens
 * - Gestão de técnicos e materiais
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
#include "../../ExameFinal/Outros/Extra/extra.h"
#include "../Logs/Funcoes/Logs.h"

// ---------------------- FUNÇÕES PRINCIPAIS ---------------------- //

/**
 * @brief Cria uma nova ordem de manutenção.
 *
 * Solicita ao utilizador:
 * - Ativo a reparar
 * - Departamento requisitante
 * - Estado, prioridade e tipo da manutenção
 * - Materiais e custos associados
 *
 * @return OrdemDeManutencao Estrutura com os dados da ordem criada
 */
OrdemDeManutencao CriarOrdemDeManutencao() {
    OrdemDeManutencao m;

    // Gera o próximo ID disponível para a ordem
    m.IdOrdem = ProximoIdManutencao();

    printf("\n----- Menu de Criação de Ordens de Manutenção -----\n");

    // Mostra todos os ativos disponíveis
    ListarAtivos();
    printf("\nId do Ativo a ser reparado: ");


    // Valida a entrada do ID do ativo
    while (scanf(" %d", &m.IdAtivo) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n');  // Limpa buffer
        printf("Id do Ativo a ser reparado: ");
    }
    getchar(); // Limpa '\n' residual

    // Atualiza estado do ativo para "EmReparacao"
    if (!AtualizarEstadoAtivo(m.IdAtivo, EmReparacao)) {
        printf("Não foi possível atualizar o estado do ativo.\n");
        return m; // Retorna ordem incompleta
    }

    // Listar departamentos e escolher requisitante
    Departamento* dep = nullptr;
    ListarDepartamentos();
    printf("\nId do Departamento requisitante: ");
    while (scanf("%d", &m.IdDepartamento) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n');
        printf("Id do Departamento requisitante: ");
    }

    // Incrementa o número de ordens no departamento escolhido
    AdicionarOrdem(m.IdDepartamento);

    // Obter a data atual
    ObterDataAtual(m.DataPedido);

    // Escolha de estado, prioridade e tipo via menus
    m.estado = Iniciado;
    m.prioridade = MenuPrioridadeOrdens();
    m.tipo = MenuTipoOrdens();

    // Registo de materiais e cálculo do custo total
    printf("\n----- Registo de Materiais -----");
    getchar(); // Limpa buffer
    m.custo = RegistarMateriaisOrdem(m.IdOrdem);

    // Adiciona custo ao departamento
    AdicionarCustoDepartamento(m.IdDepartamento, m.custo);
    getchar(); // Limpa '\n'

    // Mostrar resumo da ordem criada
    printf("\nOrdem Criada!\n");
    printf("ID da Ordem: %d | Id do ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Prioridade: %s | Tipo: %s | Custo: %.2f€\n",
           m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
           EstadoManutencaoToStr(m.estado),
           PrioridadeManutencaoToStr(m.prioridade),
           TipoManutencaoToStr(m.tipo),
           m.custo);

    // Gravação da ordem no ficheiro (modo append)
    FILE *f = fopen("../Dados/ordens.txt", "a");
    if (!f) {
        perror("Erro ao abrir ficheiro");
    }
    char linha[512];
    snprintf(linha, sizeof(linha), "%d;%d;%d;%s;%s;%s;%s;%.2f;\n",
             m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
             EstadoManutencaoToStr(m.estado),
             PrioridadeManutencaoToStr(m.prioridade),
             TipoManutencaoToStr(m.tipo),
             m.custo);
    fputs(linha, f);
    fclose(f);

    char log[100];
    sprintf(log, "Ordem %d criada (Ativo %d, Departamento %d)",
            m.IdOrdem, m.IdAtivo, m.IdDepartamento);
    RegistarLog(log);

    return m;
}

/**
 * @brief Inicia um trabalho baseado numa ordem pendente.
 *
 * - Lista ordens pendentes
 * - Solicita qual ordem iniciar
 * - Atualiza estado da ordem para "Decorrer"
 * - Permite associar técnicos disponíveis
 */
void IniciarTrabalho() {
    OrdemDeManutencao ordem = {0};
    int lista;

    lista = ListarOrdensNaoConcluidas();
    if (lista != 1) {
        printf ("\nNenhuma Ordem Pendente!!");
        return;
    }

    int idEscolhido;
    do {
        printf("\nId da ordem que deseja iniciar: ");
        scanf("%d", &idEscolhido);
        if (idEscolhido < 0) {
            printf("Id inválido!\n");
        }
        getchar(); // Limpa buffer
    }while (idEscolhido < 0);


    // Leitura do ficheiro e procura da ordem
    FILE *f = fopen("..\\Dados\\ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ordens.txt");
        return;
    }

    char linhas[200][512];
    int total = 0, encontrada = 0;

    while (fgets(linhas[total], sizeof(linhas[total]), f)) {
        int id;
        sscanf(linhas[total], "%d;%*511[^\n]", &id); // Lê apenas o ID

        if (id == idEscolhido) {
            int idAtivo, idDept;
            char data[50], estado[50], prioridade[50], tipo[50];
            float custo;

            sscanf(linhas[total], "%d;%d;%d;%49[^;];%49[^;];%49[^;];%49[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, tipo, &custo);

            // Atualiza estado da ordem para "Decorrer"
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

    // Reescreve todas as ordens com atualização
    f = fopen("..\\Dados\\ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhas[i], f);
    fclose(f);

    printf("\nOrdem %d iniciada com sucesso!\n", idEscolhido);

    // Associar técnicos ao trabalho
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

            // Evita duplicados
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
                printf("Técnico inválido ou já ocupado. Escolha outro.\n");
            }
            // Logs Tecnico
            char log[100];
            sprintf(log, "Técnico %d associado à ordem %d", idTec, idEscolhido);
            RegistarLog(log);


        } while (!sucesso);
    }

    // Escreve técnicos associados no ficheiro
    EscreverTecnicosOrdem(idEscolhido, ordem.idsTecnicos, ordem.totalTecnicos);

    printf("\nEstados dos técnicos atualizados com sucesso!");
    printf("\nTrabalho iniciado com sucesso!\n");

    //Logs Ordem encerrada
    char log[100];
    sprintf(log, "Ordem %d iniciada", idEscolhido);
    RegistarLog(log);

}

/**
 * @brief Encerrar uma ordem de trabalho.
 *
 * Atualiza:
 * - Estado da ordem para "Concluido"
 * - Liberta técnicos associados
 * - Atualiza estado do ativo e incrementa reparos
 */
void EncerrarTrabalhos() {
    int idEscolhido;
    printf("\nQual o Id da ordem que deseja finalizar: ");
    if (scanf("%d", &idEscolhido) != 1) {
        printf("Entrada inválida.\n");
        while(getchar() != '\n');
        return;
    }
    getchar();

    char linhas[200][512] = {{0}};
    int total = 0, encontrada = 0, idAtivoOrdem = -1;

    FILE *f = fopen("../Dados/ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ordens.txt");
        return;
    }

    while (fgets(linhas[total], sizeof(linhas[total]), f) && total < 200) {
        int id, idAtivo, idDept;
        char data[12], estado[20], prioridade[20], tipo[20];
        float custo;

        if (sscanf(linhas[total], "%d;%d;%d;%11[^;];%19[^;];%19[^;];%19[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, tipo, &custo) == 8) {
            if (id == idEscolhido) {

                if (strcmp(estado, "Decorrer") != 0) {
                    printf("\nA ordem %d não pode ser encerrada (estado atual: %s).\n",
                           idEscolhido, estado);
                    fclose(f);
                    return;
                }

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

    // Reescreve ficheiro com ordem encerrada
    f = fopen("../Dados/ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhas[i], f);
    fclose(f);

    printf("\nOrdem %d encerrada com sucesso!\n", idEscolhido);

    // Libertar técnicos associados à ordem
    int idsTec[10];
    int qntdTec = ObterTecnicosOrdem(idEscolhido, idsTec);

    int sucesso = 1;

    for (int i = 0; i < qntdTec; i++) {
        if (AtualizarEstadoTecnico(idsTec[i], DISPONIVEL)) {
            printf("Técnico %d libertado.\n", idsTec[i]);
        } else {
            printf("Falha ao libertar técnico %d.\n", idsTec[i]);
            sucesso = 0;
        }
    }

    if (qntdTec > 0 && sucesso) {
        printf("Todos os técnicos ligados à ordem foram libertados com sucesso.\n");
    }

    // Atualiza ativo e incrementa reparos
    if (idAtivoOrdem != -1) {
        if (AtualizarEstadoAtivo(idAtivoOrdem, EmOperacao)) {
            AdicionarReparo(idAtivoOrdem);
            printf("Ativo %d atualizado para Disponível e reparos incrementados.\n", idAtivoOrdem);
        } else {
            printf("Falha ao atualizar ativo %d.\n", idAtivoOrdem);
        }
    }
    GravarDataConclusao(idEscolhido);
    ListarTempoOrdens(idEscolhido);

    //Logs
    char log[100];
    sprintf(log, "Ordem %d encerrada", idEscolhido);
    RegistarLog(log);

}

/**
 * @brief Converte string em TipoManutencao (enum)
 * @param s String representando tipo
 * @return TipoManutencao enum correspondente
 */
TipoManutencao StrToTipoManutencao(const char* s) {
    if (strcmp(s, "Corretiva") == 0)
        return CORRETIVA;
    if (strcmp(s, "Preventiva") == 0)
        return PREVENTIVA;

    // Valor padrão se a string não corresponder
    return CORRETIVA;
}


/**
 * @brief Regista materiais usados numa ordem e calcula o custo total
 * @param idOrdem ID da ordem para registro
 * @return float custo total dos materiais
 */
float RegistarMateriaisOrdem(int idOrdem) {
    FILE *f;
    int quantidade;
    float precoPeca, subtotal, total = 0;
    char material[50];
    char continuar;

    f = fopen("../Dados/Lista_Ordens.txt", "a");
    if (!f) {
        perror("Erro ao abrir Lista_Ordens.txt");
        return 0;
    }

    fprintf(f, "Ordem nº %d\n", idOrdem);
    fprintf(f, "-----------------------------\n");

    do {
        // Quantidade
        do {
            printf("\nQuantidade: ");
        } while (scanf("%d", &quantidade) != 1 || quantidade <= 0 && (printf("Quantidade inválida.\n") || getchar()));

        getchar(); // limpa '\n'

        // Material
        printf("Material: ");
        fgets(material, sizeof(material), stdin);
        material[strcspn(material, "\n")] = '\0';

        // Preço por peça
        do {
            printf("Preço por peça: ");
        } while (scanf("%f", &precoPeca) != 1 || precoPeca < 0 && (printf("Preço inválido.\n") || getchar()));

        getchar(); // limpa '\n'

        subtotal = quantidade * precoPeca;
        total += subtotal;

        fprintf(f, "Material: %s | Quantidade: %d | Preço unitário: %.2f | Subtotal: %.2f\n",
                material, quantidade, precoPeca, subtotal);

        // Pergunta se deseja adicionar mais materiais
        printf("Adicionar outro material? (s/n): ");
        scanf("%c", &continuar);
        getchar(); // limpa '\n'
    } while (continuar == 's' || continuar == 'S');

    fprintf(f, "Total da Ordem: %.2f €\n\n", total);
    fclose(f);

    return total;
}

/**
 * @brief Obtém um departamento a partir do seu ID
 * @param id ID do departamento
 * @return Departamento* Ponteiro para struct alocada dinamicamente (NULL se não encontrado)
 */
Departamento* ObterDepartamentoPorId(int id) {
    FILE *f = fopen("../Dados/departamentos.txt", "r");
    if (!f) return NULL;

    Departamento* d = (Departamento*) malloc(sizeof(Departamento));
    if (!d) {
        fclose(f);
        return NULL;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), f)) {
        int idDept;
        char nome[50], resp[50], email[50], telefone[50];
        int ordens, estadoInt;
        float custo;

        if (sscanf(linha, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%d;%f;%d;",
                   &idDept, nome, resp, email, telefone, &ordens, &custo, &estadoInt) == 8) {
            if (idDept == id) {
                d->IdDept = idDept;
                strcpy(d->nome, nome);
                strcpy(d->responsavel, resp);
                strcpy(d->email, email);
                strcpy(d->telefone, telefone);
                d->ordens = ordens;
                d->CustoTotal = custo;
                d->estado = (EstadoDepartamento)estadoInt; // conversão segura de int para enum
                encontrado = 1;
                break;
            }
        }
    }

    fclose(f);

    if (!encontrado) {
        free(d);
        return NULL;
    }

    return d;
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
        // Ler ID da ordem
        if (sscanf(linha, "Id da Ordem: %d |", &idO) == 1) {
            if (idO == idOrdem) {
                // Procura a parte "Id tecnicos associados:"
                char *p = strstr(linha, "Id tecnicos associados:");
                if (!p) break;
                p += strlen("Id tecnicos associados:"); // Move após o texto

                // Ler todos os IDs técnicos (números separados por espaço)
                int idTec;
                while (sscanf(p, "%d", &idTec) == 1) {
                    idsTec[total++] = idTec;

                    // avança até próximo número
                    while (*p && (*p == ' ' || (*p >= '0' && *p <= '9'))) p++;
                    while (*p && *p == ' ') p++;
                }
                break; // ordem encontrada
            }
        }
    }

    fclose(f);
    return total;
}

