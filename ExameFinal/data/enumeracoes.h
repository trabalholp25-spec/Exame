//
// Created by leona on 15/12/2025.
//

#ifndef EXAMEFINAL_ENUMERACOES_H
#define EXAMEFINAL_ENUMERACOES_H

typedef enum{Operacional, EmOperacao,EmReparacao, Abatido, Inativo} EstadoEquipamento;
typedef enum {VIATURA,EQUIPAMENTO_INFORMATICO,MOBILIARIO_URBANO,FERRAMENTA,OUTRA} CategoriaAtivo;
typedef enum {Baixa,Normal,Alta} PrioridadeManutencao;
typedef enum {Iniciado, Decorrer, Concluido} EstadoManutencao;
typedef enum {DISPONIVEL,OCUPADO,FERIAS,INATIVO} EstadoTecnico;
typedef enum {ELETRICISTA,MECANICO,INFORMATICO,PEDREIRO,PINTOR,OUTRO} Especialidade;
typedef enum {ATIVO, Desativado} EstadoDepartamento;


#endif //EXAMEFINAL_ENUMERACOES_H