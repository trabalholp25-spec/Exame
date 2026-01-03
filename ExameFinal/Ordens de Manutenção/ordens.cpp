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

    // Listar ativos disponíveis para o utilizador escolher
    ListarAtivos();
    printf("\nId do Ativo a ser reparado: ");

    // Validação de entrada do ID do ativo
    while (scanf(" %d", &m.IdAtivo) != 1) {
        printf("Entrada inválida. Insira um número válido.\n");
        while (getchar() != '\n')
            printf("Id do Ativo a ser reparado: ");
    }
    getchar(); // Limpa o '\n' residual no buffer

    // Atualiza o estado do ativo para "EmReparacao"
    if (!AtualizarEstadoAtivo(m.IdAtivo, EmReparacao)) {
        printf("Não foi possível atualizar o estado do ativo.\n");
        return m; // retorna a ordem incompleta
    }

    // Listar departamentos e escolher o requisitante
    Departamento* dep = nullptr;

        ListarDepartamentos(); // Mostra todos os departamentos ativos

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

    // Validação do custo da manutenção
    printf("\n----- Registo de Materiais -----");
    getchar();
    m.custo = RegistarMateriaisOrdem(m.IdOrdem);
    AdicionarCustoDepartamento(m.IdDepartamento, m.custo);
    getchar(); // Limpa '\n'

    // Mostra resumo da ordem criada
    printf("\nOrdem Criada!\n");
    printf("ID da Ordem: %d | Id do ativo: %d | Id do Departamento: %d | Data do Pedido: %s | Estado: %s | Prioridade: %s | Tipo: %s| Custo: %.2f€\n",
           m.IdOrdem, m.IdAtivo, m.IdDepartamento, m.DataPedido,
           EstadoManutencaoToStr(m.estado),
           PrioridadeManutencaoToStr(m.prioridade),
           TipoManutencaoToStr(m.tipo),
           m.custo);

    // --- Gravação da ordem no ficheiro ---
    FILE *f = fopen("../Dados/ordens.txt", "a");
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
    getchar();

    // Lê todas as ordens para localizar a escolhida
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

    // Escreve no ficheiro de técnicos da ordem **uma única vez**
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
    return total;
}

// --- Encerrar uma ordem de trabalho ---
void EncerrarTrabalhos() {
    int idEscolhido;
    int idAtivoOrdem = -1;
    TipoManutencao tipoManutencao = PREVENTIVA;

    printf("\nQual o Id da ordem que deseja finalizar: ");
    if (scanf("%d", &idEscolhido) != 1) {
        printf("Entrada inválida.\n");
        while (getchar() != '\n'); // limpa buffer
        return;
    }
    while (getchar() != '\n'); // limpa qualquer lixo restante

    // --- Ler ordens ---
    char linhas[200][256] = {{0}};
    int total = 0;
    int encontrada = 0;

    FILE *f = fopen("../Dados/ordens.txt", "r");
    if (!f) {
        perror("Erro ao abrir ordens.txt");
        return;
    }

    while (fgets(linhas[total], sizeof(linhas[total]), f) && total < 200) {

        int id, idAtivo, idDept;
        char data[12] = {0}, estado[20] = {0}, prioridade[20] = {0}, tipoStr[20] = {0};
        float custo;

        // Formato correto: 8 campos
        if (sscanf(linhas[total],
                   "%d;%d;%d;%11[^;];%19[^;];%19[^;];%19[^;];%f;",
                   &id, &idAtivo, &idDept, data, estado, prioridade, tipoStr, &custo) == 8) {

            if (id == idEscolhido) {
                idAtivoOrdem = idAtivo;
                tipoManutencao = StrToTipoManutencao(tipoStr);

                // Reescrever a linha com estado = Concluido e mantendo todos os campos
                snprintf(linhas[total], sizeof(linhas[total]),
                         "%d;%d;%d;%s;Concluido;%s;%s;%.2f;\n",
                         id, idAtivo, idDept, data, prioridade,
                         TipoManutencaoToStr(tipoManutencao), custo);

                encontrada = 1;
            }
        } else {
            printf("Linha ignorada por formato inválido: %s\n", linhas[total]);
        }

        total++;
    }
    fclose(f);

    if (!encontrada) {
        printf("\nOrdem não encontrada!\n");
        return;
    }

    // --- Reescrever ordens ---
    f = fopen("../Dados/ordens.txt", "w");
    if (!f) {
        perror("Erro ao abrir ordens.txt para escrita");
        return;
    }
    for (int i = 0; i < total; i++)
        fputs(linhas[i], f);
    fclose(f);

    printf("\nOrdem %d encerrada com sucesso!\n", idEscolhido);

    // --- Libertar técnicos ---
    int idsTec[10] = {0};
    int qntdTec = ObterTecnicosOrdem(idEscolhido, idsTec);

    for (int i = 0; i < qntdTec; i++) {
        if (AtualizarEstadoTecnico(idsTec[i], DISPONIVEL)) {
            AdicionarTrabalhos(idsTec[i]);
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

            if (tipoManutencao == CORRETIVA) {
                AdicionarReparo(idAtivoOrdem);
                printf("Ativo %d atualizado e reparo incrementado (ordem corretiva).\n", idAtivoOrdem);
            } else {
                printf("Ativo %d atualizado (ordem não corretiva).\n", idAtivoOrdem);
            }

        } else {
            printf("Falha ao atualizar ativo %d.\n", idAtivoOrdem);
        }
    }
}

TipoManutencao StrToTipoManutencao(const char* s) {
    if (s == NULL) return PREVENTIVA; // default seguro

    // Ignorar diferenças entre maiúsculas e minúsculas
    if (strcasecmp(s, "Corretiva") == 0) return CORRETIVA;
    if (strcasecmp(s, "Preventiva") == 0) return PREVENTIVA;

    // Qualquer valor desconhecido retorna PREVENTIVA como padrão
    return PREVENTIVA;
}

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
        // Ler quantidade
        do {
            printf("\nQuantidade: ");
        } while (scanf("%d", &quantidade) != 1 || quantidade <= 0 && (printf("Quantidade inválida.\n"), 1));
        while (getchar() != '\n'); // Limpar buffer

        // Ler nome do material
        printf("Material: ");
        fgets(material, sizeof(material), stdin);
        material[strcspn(material, "\n")] = '\0'; // Remove \n

        // Ler preço por peça
        do {
            printf("Preço por peça: ");
        } while (scanf("%f", &precoPeca) != 1 || precoPeca < 0 && (printf("Preço inválido.\n"), 1));
        while (getchar() != '\n'); // Limpar buffer

        // Calcular subtotal e total
        subtotal = quantidade * precoPeca;
        total += subtotal;

        // Escrever no ficheiro
        fprintf(f,
            "Material: %s | Quantidade: %d | Preço unitário: %.2f | Subtotal: %.2f\n",
            material, quantidade, precoPeca, subtotal);

        // Perguntar se quer adicionar outro material
        printf("Adicionar outro material? (s/n): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n'); // Limpar buffer

    } while (continuar == 's' || continuar == 'S');

    fprintf(f, "Total da Ordem: %.2f €\n\n", total);
    fclose(f);

    return total;
}





