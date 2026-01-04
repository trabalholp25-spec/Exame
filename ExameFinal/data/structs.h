//
// Created by leona on 15/12/2025.
//

#ifndef EXAMEFINAL_STRUCTS_H
#define EXAMEFINAL_STRUCTS_H
#include "enumeracoes.h"

// Ativo
typedef struct {
    int IdAtv;
    char nome[50], data[11];
    char localizacao[50];
    EstadoEquipamento estado;
    CategoriaAtivo categoria;
    int reparos;
}Ativo;

// Departamento
typedef struct {
    int IdDept;
    char nome[50];
    char responsavel[50], sobrenome[50];
    char email[50];
    char telefone[15];
    EstadoDepartamento estado;
    int pedidos;
    int ordens;
    float CustoTotal;
}Departamento;

//Ordens de manutenção
typedef struct {
    int IdOrdem, IdAtivo, IdDepartamento;
    char DataPedido[12], DataFim[12];
    PrioridadeManutencao prioridade;
    EstadoManutencao estado;
    char descricao[50];
    char materiais[50];
    int quantidade;
    float custo;
    int idsTecnicos[10];
    int totalTecnicos;
    TipoManutencao tipo;
    float tempoDias;
}OrdemDeManutencao;

// Tecnico
typedef struct {
    int IdTecnico;
    char *nome;
    Especialidade especialidade;
    EstadoTecnico estado;
    char EspecialidadeExtra[50];
    int trabalhos;
}Tecnico;


#endif //EXAMEFINAL_STRUCTS_H