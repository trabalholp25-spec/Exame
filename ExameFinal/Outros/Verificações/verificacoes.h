/**
* @file verificacoes.h
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declaração de todo o tipo de funções destinadas a verificar todo o tipo de campos;
 *
 * Este ficheiro contém as funções utilizadas para gerir de entrada de dados,
 * certificando-se da sua veracidade.
 */
#ifndef EXAMEFINAL_VERIFICACOES_H
#define EXAMEFINAL_VERIFICACOES_H
#include "../../data/structs.h"

int ValidarDataAquisicao(const char *data);
void VerificarEstadoAtivo(Ativo *a);
int ValidarEmail(const char *email);

#endif //EXAMEFINAL_VERIFICACOES_H