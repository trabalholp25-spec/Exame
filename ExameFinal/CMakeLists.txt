cmake_minimum_required(VERSION 4.0)
project(ExameFinal)

set(CMAKE_CXX_STANDARD 20)

add_executable(ExameFinal main.cpp
        data/enumeracoes.h
        data/structs.h
        data/constantes.h
        "Menus/Menus Gerais/menus.cpp"
        "Menus/Menus Gerais/menus.h"
        Outros/Verificações/verificacoes.cpp
        Outros/Verificações/verificacoes.h
        Tecnicos/tecnico.cpp
        Tecnicos/tecnico.h
        Outros/Extra/extra.cpp
        Outros/Extra/extra.h
        Equipamentos/Equipamentos.cpp
        Equipamentos/Equipamentos.h
        Departamentos/departamentos.cpp
        Departamentos/departamentos.h
        "Ordens de Manutenção/ordens.cpp"
        "Ordens de Manutenção/ordens.h"
        "Menus/Menus Ordens/menu_ordens.cpp"
        "Menus/Menus Ordens/menu_ordens.h"
        "Menus/Menus Equipamentos/menus_equipamentos.cpp"
        "Menus/Menus Equipamentos/menus_equipamentos.h"
        "Menus/Menus Tecnicos/menus_tecnicos.cpp"
        "Menus/Menus Tecnicos/menus_tecnicos.h"
        "Menus/Menus Departamentos/menu_departamentos.cpp"
        "Menus/Menus Departamentos/menu_departamentos.h"
        Listagem/Equipamentos/leitura_equipamentos.cpp
        Listagem/Equipamentos/leitura_equipamentos.h
        Listagem/Tecnicos/leitura_tecnicos.cpp
        Listagem/Tecnicos/leitura_tecnicos.h
        Listagem/Departamentos/leitura_departamentos.cpp
        Listagem/Departamentos/leitura_departamentos.h
        Listagem/Ordens/leitura_ordens.cpp
        Listagem/Ordens/leitura_ordens.h
        "Menus/Menu relatórios/menus_administracao.cpp"
        "Menus/Menu relatórios/menus_administracao.h"
        Logs/Funcoes/Logs.cpp
        Logs/Funcoes/Logs.h
)
