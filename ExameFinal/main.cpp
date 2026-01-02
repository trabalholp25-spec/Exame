#include <stdio.h>
#include <windows.h>
#include "Departamentos/departamentos.h"
#include "Menus/Menus Gerais/menus.h"
#include "Tecnicos/tecnico.h"
#include "data/structs.h"
#include "Equipamentos/Equipamentos.h"
#include "Ler/Departamentos/leitura_departamentos.h"
#include "Ler/Equipamentos/leitura_equipamentos.h"
#include "Ler/Ordens/leitura_ordens.h"
#include "Ler/Tecnicos/leitura_tecnicos.h"
#include "Menus/Menus Equipamentos/menus_equipamentos.h"
#include "Menus/Menus Ordens/menu_ordens.h"
#include "Menus/Menus Tecnicos/menus_tecnicos.h"
#include "Ordens de Manutenção/ordens.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IONBF, 0);

    int escolha1, escolha2, escolha3, continuar;

    // Testes / Debugs
    printf ("Ativo:\n");
    ListarAtivos();
    printf ("Tecnicos:\n");
    ListarTecnicos();
    printf ("Departamentos:\n");
    ListarDepartamentos();
    printf("Ordens:\n");
    ListarOrdens();

    do {
        escolha1 = Menu1();

        switch (escolha1) {

            case 1: // Ativos
                escolha2 = MenuAtivos();

                switch (escolha2) {
                    case 1:
                        CriarEquipamento();
                        break;
                    case 2:
                        escolha3 = MenuListarAtivos();

                        switch (escolha3) {
                            case 1: // Listar Ativos por Categoria
                                ListarAtivosPorCategoria();
                                break;
                            case 2: // Listar Ativos por Estado
                                ListarAtivosPorEstado();
                                break;
                            case 3:
                                ListarAtivos();
                                break;
                            case 0:
                                printf("A voltar...");
                                break;
                        }
                        break;
                    case 3:
                        ListarAtivos();
                        EliminarAtivos();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opção inválida.\n");
                }
                break;

            case 2: // Departamentos
                escolha2 = MenuDepartamentos();

                switch (escolha2) {
                    case 1:
                        CriarDepartamento();
                        break;
                    case 2:
                        ListarDepartamentos();
                        break;
                    case 3:
                        ListarDepartamentos();
                        DesativarDepartamento();
                        break;
                    case 0:
                        printf("A voltar...\n");
                        break;
                }
                break;

            case 3: // Ordem de Manutenção
                CriarOrdemDeManutencao();
                break;

            case 4: // Técnicos
                escolha2 = MenuTecnicos();

                switch (escolha2) {
                    case 1:
                        CriarTecnico();
                        break;
                    case 2:
                        ListarTecnicos();
                        break;
                    case 3:
                        ListarTecnicos();
                        EliminarTecnico();
                        break;
                    case 4: // dentro de ordens.cpp
                        escolha3 = MenuGestao();

                        switch (escolha3) {
                            case 1:
                                ListarOrdens();
                                break;
                            case 2:
                                IniciarTrabalho();
                                break;
                            case 3:
                                continuar = ListarOrdensNaoConcluidas();
                                if (continuar == 0) {
                                    printf ("\nNão foi encontrada nenhuma ordem pendente!");
                                    break;
                                }
                                EncerrarTrabalhos();
                                break;
                            case 0:
                                printf("\nA voltar...");
                                break;
                        }
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opção inválida.\n");
                }
                break;
            case 5: // Relatórios
                break;
            case 0:
                printf("A sair...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (escolha1 != 0);

    return 0;
}
