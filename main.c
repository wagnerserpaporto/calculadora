#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "expressao.h"


void executarOperacoesDeTeste() {
    printf("\n--- Executando operacoes de teste ---\n");

    char *expressoesPosfixas[33] = {
        "-5 3 +",
        "-5 + 3",
        "2 * -4",
        "2 -4 *",
        "(-1) * (-2)",
        "-1 -2 *",
        "3.5 + 2.5",
        "3.5 2.5 +",
        "5.5 10.2 -",
        "5.5 - 10.2",
        "6 2.0 /",
        "6 / 2.0",
        "4 / 0",
        "4 0 /",
        "(-3.3) * 2",
        "-3.3 2 *",
        "(7 - 3.5) / 3.5",
        "7 3.5 - 3.5 /",
        "((200+3) * (-1.5))",
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

    for (int i = 0; i < 33; i++) {
        printf("Testando expressao: %s\n", expressoesPosfixas[i]);
        double resultado = resolveRPN(expressoesPosfixas[i]);
        printf("Resultado: %.2f\n\n", resultado);
    }
}

void entrarComExpressao(char etipo) {
	printf("Digite a Expressao: ");
	//valida o tipo da expressão e então converte e resolve a expressão
	if(etipo == 'i'){
	    char *resultadoPosfixa = recebe_infixa();
	    double resultado = resolveRPN(resultadoPosfixa);
	    printf("\nValor RPN: %.2f\n", resultado);
	}else{
		char* expr = lerExpressaoDinamica();
		char *resultadoInfixa = recebe_posfixa(expr);
		printf("expressão final %s\n", resultadoInfixa);
		double resultado = resolveRPN(expr);
		
		
	}
}


int main(void) {
    setlocale(LC_ALL, "");
    int opcao;

    do {
        printf("\n=========== CALCULADORA POLONESA ==========\n");
		printf("1 - Entrar com expressao infixada\n");
        printf("2 - Entrar com expressao pós-fixada\n");
        printf("3 - Executar operacoes de teste\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
			case 1:
				entrarComExpressao('i');
				//i para infixada
				break;
            case 2:
                entrarComExpressao('p');
				//p para pós fixada
                break;
            case 3:
                executarOperacoesDeTeste();
                break;
            case 4:
                printf("Saindo... Valeu, campeão!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 3);

    return 0;
}
