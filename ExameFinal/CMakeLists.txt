cmake_minimum_required(VERSION 4.0)
project(ExameFinal)

set(CMAKE_CXX_STANDARD 20)

add_executable(ExameFinal main.cpp
        data/enumeracoes.h
        data/structs.h
        data/constantes.h
        "Menus/Menus Gerais/menus.cpp"
        "Menus/Menus Gerais/menus.h"
        Verificacoes.cpp
        verificacoes.h
        Tecnicos/tecnico.cpp
        Tecnicos/tecnico.h
        extra.cpp
        extra.h
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
        Ler/Equipamentos/leitura_equipamentos.cpp
        Ler/Equipamentos/leitura_equipamentos.h
        Ler/Tecnicos/leitura_tecnicos.cpp
        Ler/Tecnicos/leitura_tecnicos.h
        Ler/Departamentos/leitura_departamentos.cpp
        Ler/Departamentos/leitura_departamentos.h
        Ler/Ordens/leitura_ordens.cpp
        Ler/Ordens/leitura_ordens.h
)
