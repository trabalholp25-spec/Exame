//
// Created by leona on 23/12/2025.
//
#include <stdio.h>
#include "../../Menus/Menus Tecnicos/menus_tecnicos.h"
#include "leitura_tecnicos.h"
#include "../../data/structs.h"

#include <cstdlib>
#include <cstring>

void ListarTecnicos() {

    FILE *f = fopen("..\\Dados\\tecnicos.txt", "r");
    if (f == NULL) {
        exit(EXIT_FAILURE);
    }

    Tecnico t;
    char bufferEsp[50], bufferEst[50];
    char linha[256];

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d; %49[^;]; %49[^;]; %49[^;]; %49[^;];",
       &t.IdTecnico, t.nome, t.sobrenome, bufferEsp, bufferEst)) {

            t.especialidade = StrToEspecialidade(bufferEsp);
            t.estado = StrToEstadoTecnico(bufferEst);

            if (t.estado != INATIVO) {
                printf("Id:%d | Nome:%s %s | Especialidade:%s | Estado:%s\n",
                       t.IdTecnico,
                       t.nome,
                       t.sobrenome,
                       EspecialidadeToStr(t.especialidade),
                       EstadoTecnicoToStr(t.estado));
            }
                   }
    }

    fclose(f);
}

EstadoTecnico StrToEstadoTecnico(const char *s) {
    if (strcmp(s, "Disponível") == 0) return DISPONIVEL;
    if (strcmp(s, "Ocupado") == 0)    return OCUPADO;
    if (strcmp(s, "Férias") == 0)     return FERIAS;
    if (strcmp(s, "Inativo") == 0)    return INATIVO;
    return INATIVO; // default
}

Especialidade StrToEspecialidade(const char *s) {
    if (strcmp(s, "Eletricista") == 0) return ELETRICISTA;
    if (strcmp(s, "Mecânico") == 0)    return MECANICO;
    if (strcmp(s, "Informático") == 0) return INFORMATICO;
    if (strcmp(s, "Pedreiro") == 0)    return PEDREIRO;
    if (strcmp(s, "Pintor") == 0)      return PINTOR;
    if (strcmp(s, "Outro") == 0)       return OUTRO;
    return OUTRO; // default
}