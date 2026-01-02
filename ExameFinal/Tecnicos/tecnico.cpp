#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data/structs.h"
#include "../Menus/Menus Gerais/menus.h"
#include "../Menus/Menus Tecnicos/menus_tecnicos.h"
#include "../extra.h"
#include "../Ler/Tecnicos/leitura_tecnicos.h"
#include "../Tecnicos/tecnico.h"

Tecnico CriarTecnico() {
    Tecnico t;
    t.IdTecnico = ProximoIdTecnico();

    printf("\n----- Menu de Criação -----\n");

    t.nome = (char *)malloc(50 * sizeof(char));
    if (t.nome == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    // LIMPAR BUFFER ANTES DE fgets()
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Nome do técnico: ");
    fgets(t.nome, 50, stdin);
    t.nome[strcspn(t.nome, "\n")] = 0;

    t.especialidade = MenuEspecialidade();
    t.estado = MenuEstado();

    printf("Id Tecnico:%d | Nome:%s | Especialidade:%s | Estado:%s\n",
           t.IdTecnico, t.nome,
           EspecialidadeToStr(t.especialidade),
           EstadoTecnicoToStr(t.estado));

    // Gravar no ficheiro
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "a");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        free(t.nome);
        exit(1);
    }

    fprintf(f, "%d; %s; %s; %s;\n",
            t.IdTecnico,
            t.nome,
            EspecialidadeToStr(t.especialidade),
            EstadoTecnicoToStr(t.estado));
    fclose(f);

    free(t.nome);
    t.nome = NULL;

    return t;
}

void EliminarTecnico() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    printf("Introduza o ID do técnico a eliminar: ");
    scanf("%d", &id);
    getchar(); // limpar \n do buffer do scanf

    Tecnico lista[200];
    int n = 0;
    char bufferNome[256], bufferEsp[50], bufferEst[50];

    // Ler técnicos do ficheiro
    while (fgets(bufferNome, sizeof(bufferNome), f) && n < 200) {
        char linha[512];
        strcpy(linha, bufferNome);

        if (sscanf(linha, "%d ; %255[^;] ; %49[^;] ; %49[^;] ;",
                   &lista[n].IdTecnico,
                   bufferNome,
                   bufferEsp,
                   bufferEst) == 4) {

            // Alocar memória para o nome
            lista[n].nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!lista[n].nome) {
                printf("Erro de memória.\n");
                exit(1);
            }
            strcpy(lista[n].nome, bufferNome);

            lista[n].especialidade = StrToEspecialidade(bufferEsp);
            lista[n].estado = StrToEstadoTecnico(bufferEst);

            n++;
        }
    }
    fclose(f);

    // Procurar e marcar como INATIVO
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdTecnico == id) {
            lista[i].estado = INATIVO;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Técnico com ID %d não encontrado.\n", id);
        // Libertar memória antes de sair
        for (int i = 0; i < n; i++)
            free(lista[i].nome);
        return;
    }

    // Reescrever o ficheiro
    f = fopen("..\\Dados\\tecnicos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        for (int i = 0; i < n; i++)
            free(lista[i].nome);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d; %s; %s; %s;\n",
                lista[i].IdTecnico,
                lista[i].nome,
                EspecialidadeToStr(lista[i].especialidade),
                EstadoTecnicoToStr(lista[i].estado));

        free(lista[i].nome); // Libertar memória
    }

    fclose(f);

    printf("Técnico com ID %d marcado como Inativo.\n", id);
}

void AtivarTecnico() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (!f) {
        printf("Não foi possível abrir o ficheiro.\n");
        return;
    }

    int id;
    printf("\nIntroduza o Id do Técnico a Ativar: ");
    scanf("%d", &id);
    getchar(); // limpar buffer

    Tecnico lista[200];
    int n = 0;
    char bufferNome[256], bufferEsp[50], bufferEst[50];

    while (fgets(bufferNome, sizeof(bufferNome), f) && n < 200) {
        char linha[512];
        strcpy(linha, bufferNome);

        if (sscanf(linha, "%d ; %255[^;] ; %49[^;] ; %49[^;] ;",
                   &lista[n].IdTecnico,
                   bufferNome,
                   bufferEsp,
                   bufferEst) == 4) {

            lista[n].nome = (char *)malloc(strlen(bufferNome) + 1);
            if (!lista[n].nome) {
                printf("Erro de memória.\n");
                exit(1);
            }
            strcpy(lista[n].nome, bufferNome);

            lista[n].especialidade = StrToEspecialidade(bufferEsp);
            lista[n].estado = StrToEstadoTecnico(bufferEst);

            n++;
        }
    }
    fclose(f);

    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].IdTecnico == id) {
            lista[i].estado = DISPONIVEL;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Técnico com ID %d não encontrado.\n", id);
        for (int i = 0; i < n; i++)
            free(lista[i].nome);
        return;
    }

    f = fopen("..\\Dados\\tecnicos.txt", "w");
    if (!f) {
        printf("Não foi possível reabrir o ficheiro.\n");
        for (int i = 0; i < n; i++)
            free(lista[i].nome);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d; %s; %s; %s;\n",
                lista[i].IdTecnico,
                lista[i].nome,
                EspecialidadeToStr(lista[i].especialidade),
                EstadoTecnicoToStr(lista[i].estado));

        free(lista[i].nome); // Libertar memória
    }

    fclose(f);

    printf("Técnico com ID %d marcado como Ativo.\n", id);
}

int AtualizarEstadoTecnico(int idTecnico, EstadoTecnico novoEstado) {
    FILE *f = fopen("../Dados/tecnicos.txt", "r");
    if (!f) {
        perror("Erro ao abrir o ficheiro de técnicos");
        return 0;
    }

    Tecnico tecnicos[200];
    int total = 0;
    int encontrado = 0;

    char linha[512];
    char bufferNome[256], bufferEsp[50], bufferEst[50];

    /* LEITURA DO FICHEIRO */
    while (fgets(linha, sizeof(linha), f) && total < 200) {

        if (sscanf(linha, "%d;%255[^;];%49[^;];%49[^;];",
                   &tecnicos[total].IdTecnico,
                   bufferNome,
                   bufferEsp,
                   bufferEst) == 4) {

            tecnicos[total].nome = (char*) malloc(strlen(bufferNome) + 1);
            if (!tecnicos[total].nome) {
                perror("Erro ao alocar memória");
                fclose(f);
                for (int i = 0; i < total; i++)
                    free(tecnicos[i].nome);
                return 0;
            }

            strcpy(tecnicos[total].nome, bufferNome);
            tecnicos[total].especialidade = StrToEspecialidade(bufferEsp);
            tecnicos[total].estado = StrToEstadoTecnico(bufferEst);
            total++;
        }
    }
    fclose(f);

    /* ATUALIZAÇÃO DO ESTADO */
    for (int i = 0; i < total; i++) {
        if (tecnicos[i].IdTecnico == idTecnico) {

            if (tecnicos[i].estado == novoEstado) {
                printf("O técnico já se encontra nesse estado.\n");
                goto limpar;
            }

            tecnicos[i].estado = novoEstado;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Técnico não encontrado.\n");
        goto limpar;
    }

    /* ESCRITA SEGURA EM FICHEIRO TEMPORÁRIO */
    f = fopen("../Dados/tecnicos_tmp.txt", "w");
    if (!f) {
        perror("Erro ao criar ficheiro temporário");
        goto limpar;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%s;%s;\n",
                tecnicos[i].IdTecnico,
                tecnicos[i].nome,
                EspecialidadeToStr(tecnicos[i].especialidade),
                EstadoTecnicoToStr(tecnicos[i].estado));
    }
    fclose(f);

    remove("../Dados/tecnicos.txt");
    rename("../Dados/tecnicos_tmp.txt", "../Dados/tecnicos.txt");

    printf("Estado do técnico %d atualizado para %s.\n",
           idTecnico, EstadoTecnicoToStr(novoEstado));

limpar:
    for (int i = 0; i < total; i++)
        free(tecnicos[i].nome);

    return encontrado;
}

