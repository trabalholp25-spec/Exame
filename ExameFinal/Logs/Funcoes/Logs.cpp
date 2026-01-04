/**
* @file Logs.cpp
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Função geral para a geração das Logs
 *
 * Este ficheiro contém as funções utilizadas para gerar as logs em todo o tipo de Campos.
 */


#include "Logs.h"
#include <stdio.h>
#include <time.h>

void RegistarLog(const char *mensagem) {
    FILE *f = fopen("../Logs/sistema.log", "a");
    if (!f) return;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char dataHora[20];
    strftime(dataHora, sizeof(dataHora), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(f, "[%s] %s\n", dataHora, mensagem);

    fclose(f);
}


