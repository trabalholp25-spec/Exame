//
// Created by leona on 16/12/2025.
//

#include <cstring>
#include <stdio.h>

#include "data/enumeracoes.h"
#include "data/structs.h"

int VerificarEscolha(int min, int max, int valor) {
    if (valor > min && valor < max) {
        return 1;
    } else {
        return 0;
    }
}

int ValidarDataAquisicao(const char *data){
        int dia, mes, ano;

        // Verificar formato DD/MM/AAAA
        if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3)
            return 0;

        // Ano válido
        if (ano < 1900 || ano > 2025)
            return 0;

        // Mês válido
        if (mes < 1 || mes > 12)
            return 0;

        // Dias por mês
        int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

        // Ano bissexto
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
            diasMes[1] = 29;

        // Dia válido
        if (dia < 1 || dia > diasMes[mes - 1])
            return 0;

        return 1; // Data válida
}

void VerificarEstadoAtivo(Ativo *a) {
    if (a->estado == EmReparacao) {
        a->reparos++;
    }
}

int ValidarEmail(char email[]){

    int b, contador = 0, a = 0;

     if(strlen(email) >= 50) {
         printf("Erro em validar email\n");
     } else {
         for (b = 0; b < strlen(email); b++) {
             if (email[b] == '@') {
                 contador++;
             }
         }
         printf("Quantidade de @ no email é:%d", contador);
     }

    if (contador == 1) {
        printf("Email Válido\n");
        a = 1;
    } else {
        printf("Erro em validar email\n");
        a = 0;
    }

    return a;
}

