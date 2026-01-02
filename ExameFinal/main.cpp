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
#include "Menus/Menu relatórios/menus_administracao.h"
#include "Menus/Menus Equipamentos/menus_equipamentos.h"
#include "Menus/Menus Ordens/menu_ordens.h"
#include "Menus/Menus Tecnicos/menus_tecnicos.h"
#include "Ordens de Manutenção/ordens.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, NULL, _IONBF, 0);

    int escolha1, escolha2, escolha3,escolha4 ,continuar, total = 0;

    // Testes / Debugs
    printf ("Ativo:\n");
    ListarAtivos();
    printf ("Tecnicos:\n");
    ListarTecnicos();
    printf ("Tecnicos Inativos:\n");
    ListarTecnicosInativos();
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
                            default:
                                printf("Opção inválida.\n");
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
                    case 4:
                        ListarDepartamentosDesativados();
                        ReativarDepartamento();
                        break;
                    case 0:
                        printf("A voltar...\n");
                        break;
                    default:
                        printf("Opção inválida.\n");
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
                            default:
                                printf("Opção inválida.\n");
                        }
                        break;
                    case 5:
                        ListarTecnicosInativos();
                        AtivarTecnico();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opção inválida.\n");
                }
                break;
            case 5: // Relatórios

                escolha2 = MenuAdministracao();

                switch (escolha2) {
                    case 1: // Administração dos Ativos
                        escolha3 = MenuRelatoriosAtivos();

                        switch (escolha3) {
                            case 1:
                                total = AtivosExistentes();
                                printf("\nExistem %d Ativos registados!\n", total);
                                break;
                            case 2:
                                escolha4 = MenuListagemAtivos();

                                switch (escolha4) {
                                    case 1:
                                        ListarAtivosPorCategoria();
                                        break;
                                    case 2:
                                        ListarAtivosPorEstado();
                                        break;
                                    case 0:
                                        break;
                                    default:
                                        printf("Opção inválida.\n");
                                }
                                break;
                            case 3:
                                break;
                            case 0:
                                break;
                        }
                        break;
                    case 2: // Administração dos Departamentos
                        escolha3 = MenuRelatoriosDept();
                        break;
                    case 3:
                        escolha3 = MenuRelatoriosOrdens();

                        switch (escolha3) {
                            case 1:
                                escolha4 = MenuListagemOrdens();

                                switch (escolha4) {
                                    case 1:
                                        ListarOrdensPorEstado();
                                        break;
                                    case 2:
                                        ListarOrdensPorTipo();
                                        break;
                                    case 3:
                                        ListarOrdensPorPrioridade();
                                        break;
                                    case 4:
                                        ListarOrdensConcluidas();
                                        break;
                                    case 0:
                                        break;
                                }
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            case 0:
                                break;
                        }
                        break;
                    case 4:
                        escolha3 = MenuRelatoriosTecnicos();

                        switch (escolha3) {
                            case 1:
                                escolha4 = MenuListagemTecnicos();

                                switch (escolha4) {
                                    case 1:
                                        break;
                                    case 2:
                                        break;
                                    case 0:
                                        break;
                                }
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            case 0:
                                printf("\nA voltar...");
                                break;
                            default:
                                printf("Opção inválida.\n");
                        }
                        break;
                    case 0:
                        printf("A sair...\n");
                        break;

                    default:
                        printf("Opção inválida.\n");
                }

        }
    }while (escolha1 != 0);

        return 0;
}
