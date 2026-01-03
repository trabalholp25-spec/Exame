/**
* @file departamentos.cpp
 * @author Grupo 37
 * @date 31-12-2025
 * @version 1
 *
 * @copyright Copyright (C) Grupo37 2025. All Rights MIT Licensed.
 *
 * @brief Funções gerais do tópico "departamentos"
 *
 * Este ficheiro contém as funções utilizadas para gerir departamentos,
 * incluindo criação de um novo departamento e marcação de departamentos como inativos(eliminar departamentos).
 */

#ifndef EXAMEFINAL_DEPARTAMENTOS_H
#define EXAMEFINAL_DEPARTAMENTOS_H
#include "../data/structs.h"

Departamento CriarDepartamento();
const char* EstadoParaTexto(EstadoDepartamento estado);
void DesativarDepartamento();
void ReativarDepartamento();
void AdicionarOrdem(int id);
void AdicionarCustoDepartamento(int idDept, float valor);

#endif //EXAMEFINAL_DEPARTAMENTOS_H