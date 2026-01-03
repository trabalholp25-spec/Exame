/**
* @file verificacoes.cpp
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Todo o tipo de funções destinadas a verificar todo o tipo de campos;
 *
 * Este ficheiro contém as funções utilizadas para gerir de entrada de dados,
 * certificando-se da sua veracidade.
 */

#include <cstring>
#include <stdio.h>

#include "../../data/enumeracoes.h"
#include "../../data/structs.h"

// --- Verifica se um valor está dentro de um intervalo exclusivo (min < valor < max) ---
// Retorna 1 se estiver dentro, 0 caso contrário.
int VerificarEscolha(int min, int max, int valor) {
    if (valor > min && valor < max) {
        return 1;
    } else {
        return 0;
    }
}
// OBS: Se quiseres incluir os limites, basta usar >= e <=. Útil para menus ou seleções numéricas.

// --- Valida uma data no formato DD/MM/AAAA ---
// Critérios:
//   - Formato correto (DD/MM/AAAA)
//   - Ano válido entre 1900 e 2025
//   - Mês válido (1 a 12)
//   - Dia válido considerando meses e anos bissextos
int ValidarDataAquisicao(const char *data){
    int dia, mes, ano;

    // Verifica se sscanf conseguiu ler dia, mês e ano
    if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3)
        return 0;

    // Ano dentro de limites válidos
    if (ano < 1900 || ano > 2025)
        return 0;

    // Mês válido
    if (mes < 1 || mes > 12)
        return 0;

    // Número de dias por mês (fevereiro = 28, ajusta se bissexto)
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
        diasMes[1] = 29;

    // Dia válido
    if (dia < 1 || dia > diasMes[mes - 1])
        return 0;

    return 1; // Data válida
}

// --- Incrementa o contador de reparos de um ativo se ele estiver em reparação ---
// Recebe ponteiro para o ativo.
void VerificarEstadoAtivo(Ativo *a) {
    if (a->estado == EmReparacao) {
        a->reparos++;
    }
}

// --- Valida um email básico ---
// Critérios:
//   - Apenas um '@' no texto
//   - Não ultrapassa 50 caracteres
// Retorna 1 se válido, 0 caso contrário
int ValidarEmail(const char *email) {
    if (!email) return 0; // protege contra ponteiro nulo

    int arroba = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') arroba++;
        if (i >= 49) break; // não ultrapassa o tamanho do buffer
    }

    return (arroba == 1); // válido se tiver exatamente 1 '@'
}


