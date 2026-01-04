/**
* @file extra.h
 * @author Grupo 37
 * @date 03-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Declaração de todo o tipo de funções extras;
 *
 * Este ficheiro contém as funções utilizadas para gerir todo o tipo de Ids,
 * limpeza do buffer e obter a data atual.
 */

#ifndef EXAMEFINAL_EXTRA_H
#define EXAMEFINAL_EXTRA_H

void LimparBuffer();
int ProximoIdTecnico();
int ProximoIdAtivo();
int ProximoIdDept();
int ProximoIdManutencao();
void ObterDataAtual(char data[]);
void GravarDataConclusao(int idOrdem);
void ListarTempoOrdens(int idOrdem);
void ListarOrdensPorTempo();

#endif //EXAMEFINAL_EXTRA_H