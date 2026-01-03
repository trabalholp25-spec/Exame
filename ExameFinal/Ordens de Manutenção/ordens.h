/**
* @file ordens.h
 * @author Grupo 37
 * @date 27-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico "ordens"
 *
 * Este ficheiro contém as declarações das funções utilizadas para gerir todo o tipo de ordens.
 */

#ifndef EXAMEFINAL_ORDENS_H
#define EXAMEFINAL_ORDENS_H
#include "../data/structs.h"

OrdemDeManutencao CriarOrdemDeManutencao();
void IniciarTrabalho();
int tecnicoSelecionado(int id, int ids[], int qntd);
void EncerrarTrabalhos();
void escreverOrdemTecnicos(const OrdemDeManutencao *ordem);
int ObterTecnicosOrdem(int idOrdem, int idsTec[]);
int EscreverTecnicosOrdem(int idOrdem, int idsTec[], int totalTec);

#endif //EXAMEFINAL_ORDENS_H