#include <stdio.h>
#include <stdlib.h>

#include "convertein_posfixa.h"
#include "expressao.h"


int main(void) {
    /*printf("Digite a Expressao Infixa: ");
    char* resultadoPosfixa = recebe_infixa();
    double resultado = resolveRPN(resultadoPosfixa);

    printf("Valor RPN: %.2f\n", resultado);*/

    char *expressoesPosfixas[23] = {
        "-5 3 +",
        "2 -4 *",
        "-1 -2 *",
        "3.5 2.5 +",
        "5.5 10.2 -",
        "6 2.0 /",
        "4 0 /",
        "-3.3 2 *",
        "7 3.5 - 3.5 /",
        "2 3 + -1.5 *",
        "2 3 ^", // 8
        "16 sqrt", // 4
        "1 log", // 0
        "0 cos", // 1
        "1.5708 sen", // ≈1
        "3 2 + 2 ^", // 25
        "9 sqrt 16 sqrt +", // 7
        "2.71828 log", // ≈1
        "3.1416 cos", // ≈-1
        "4 2 / 1 1 + ^", // 4
        "-1 log", // Erro esperado (log de número negativo)
        "3 4 2 * + 5 sen -",
        "3 4 + 1 * 5 sen +"
    };

    //calcularPosfixa(resultadoPosfixa);  // Sua função da calculadora
    for (int i = 0; i < 23; i++) {
        printf("Testando expressao pos-fixa: %s\n", expressoesPosfixas[i]);
        double resultado = resolveRPN(expressoesPosfixas[i]);
        printf("Resultado: %.2f\n\n", resultado);
    }


    //free(resultadoPosfixa);
    return 0;
}
