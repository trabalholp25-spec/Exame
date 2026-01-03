//
// Created by leona on 16/12/2025.
//

#include "extra.h"
#include <time.h>
#include <stdio.h>

// Função genérica para limpar o buffer do stdin
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // descarta todos os caracteres até encontrar '\n' ou EOF
    }
}

int ProximoIdTecnico() {
    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (!f) return 1;

    int maxId = 0;
    int id;
    char nome[50], esp[50], est[50];

    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^;];",
                  &id, nome, esp, est) == 4) {
        if (id > maxId)
            maxId = id;
                  }

    fclose(f);
    return maxId + 1;
}


int ProximoIdAtivo() {
    FILE *f = fopen("..\\Dados\\ativos.txt", "r");
    if (!f) return 1; // se não existe ficheiro, começa em 1

    int maxId = 0;
    int id;
    char nome[50], loc[50], data[50], cat[50], est[50];

    while (fscanf(f, "%d;%49[^;];%49[^;];%49[^;];%49[^;];%49[^;\n]\n",&id, nome, loc, data, cat, est) == 6)
    {
        if (id > maxId)
            maxId = id;
    }

    fclose(f);
    return maxId + 1;
}

int ProximoIdDept() {
    FILE *f = fopen("..\\Dados\\departamentos.txt", "r");
    if (!f) return 1; // se não existe ficheiro, começa em 1

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



int ProximoIdManutencao() {
    FILE *f = fopen("../Dados/ordens.txt", "r");
    if (!f) return 1; // se não existe ficheiro, começa em 1

    int maxId = 0;
    int id;
    char buffer[256]; // descarta o resto da linha

    while (fgets(buffer, sizeof(buffer), f)) {
        if (sscanf(buffer, "%d;", &id) == 1) {
            if (id > maxId)
                maxId = id;
        }
    }

    fclose(f);
    return maxId + 1;
}



void ObterDataAtual(char data[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(data, "%02d/%02d/%04d",
            tm.tm_mday,
            tm.tm_mon + 1,
            tm.tm_year + 1900);
}
