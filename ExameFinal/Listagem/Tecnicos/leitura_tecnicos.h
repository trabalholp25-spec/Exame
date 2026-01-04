/**
* @file leitura_tecnicos.h
 * @author Grupo 37
 * @date 04-01-2026
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico da listagem de tecnicos.
 *
 * Este ficheiro contém funções utilizadas para listar os técnicos,
 * podendo aplicar filtros por estado, etc...
 */
#ifndef EXAMEFINAL_LEITURA_TECNICOS_H
#define EXAMEFINAL_LEITURA_TECNICOS_H

void ListarTecnicos();
void ListarTecnicosInativos();
Especialidade StrToEspecialidade(const char *s);
EstadoTecnico StrToEstadoTecnico(const char *s);
void ListarTecnicosPorCategoria();
void ListarTecnicosPorDisp();

#endif //EXAMEFINAL_LEITURA_TECNICOS_H