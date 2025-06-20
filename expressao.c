#include "expressao.h"

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

Pilha *criar_pilha() {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a pilha.\n");
        return NULL;
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

void empilhar(Pilha *pilha, double valor) {
    //void empilhar(Pilha *pilha, int valor)
    Node *novo_node = malloc(sizeof(Node));

    if (!novo_node) {
        printf("Falha ao alocar memória para novo node");
        return;
    }

    novo_node->valor = valor;
    novo_node->proximo = pilha->topo;
    pilha->topo = novo_node;
    pilha->tamanho++;
}

double desempilhar(Pilha *pilha) {
    //int desempilhar(Pilha *pilha)
    Node *temp = pilha->topo;
    if (temp == NULL) {
        printf("Operacao invalida");
        return -1;
    }
    pilha->topo = temp->proximo;
    double valor = temp->valor;

    free(temp);
    pilha->tamanho--;
    printf("DEBUG: Desempilhado: %.2f\n", valor);
    return valor;
}

/*int peek(Pilha *pilha) //essa equivale a consutarTopo
{
    return pilha->topo;
}*/
double consultarTopo(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return pilha->topo->valor; //return pilha->topo->valor;
}

int estaVazia(Pilha *pilha) {
    if (pilha->topo == NULL) {
        return 1;
    }
    return 0;
}

int tamanhoPilha(Pilha *pilha) {
    return pilha->tamanho;
}

void liberarPilha2(Pilha *p) {
    while (!estaVazia(p)) {
        desempilhar(p);
    }
    free(p);
}

int realizarOperacao(int y, int x, char operador) {
    int resultado;
    switch (operador) {
        case '+':
            resultado = y + x;
            break;
        case '-':
            resultado = y - x;
            break;
        case '*':
            resultado = y * x;
            break;
        case '/':
            resultado = y / x;
            break;
        case '^':
            resultado = potencia(y, x);
            break;
        case 'rad':
            resultado = radiciacao(y);
            break;
        case 'sen':
            resultado = seno(y);
            break;
        case 'cos':
            resultado = cosseno(y);
            break;
        default:
            resultado = 0;
            break;
    }
    return resultado;
}

int resolverPosFix(Pilha *pilha, char expressao[]) {
    int tamanho = strlen(expressao);

    for (int i = 0; i < tamanho; i++) {
        if (pilha->tamanho == 1)
            break;
        int numero;
        if (TryParse(expressao[i], &numero)) {
            empilhar(pilha, numero);
        } else {
            int x = desempilhar(pilha);
            int y = desempilhar(pilha);
            int res = realizarOperacao(y, x, expressao[i]);
            empilhar(pilha, res);
        }
    }

    return pilha->topo->valor; //return pilha->topo->valor;
}

int potencia(int base, int expoente) {
    int resultado = 1;
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return resultado;
}

int radiciacao(int numero) {
    float raiz = numero / 2;
    float temp = 0;
    while (raiz != temp) {
        temp = raiz;
        raiz = (numero / temp + temp) / 2;
    }
    return raiz;
}

int seno(int angulo) {
    float resultado = angulo;
    float termo = angulo;
    int n = 1;
    for (int i = 1; i <= 10; i++) {
        termo *= -1 * angulo * angulo / ((2 * n) * (2 * n + 1));
        resultado += termo;
        n++;
    }
    return resultado;
}

int cosseno(int angulo) {
    float resultado = 1;
    float termo = 1;
    int n = 1;
    for (int i = 1; i <= 10; i++) {
        termo *= -1 * angulo * angulo / ((2 * n - 1) * (2 * n));
        resultado += termo;
        n++;
    }
    return resultado;
}

bool TryParse(char n, int *result) {
    if (n >= '0' && n <= '9') {
        char str[2] = {n, '\0'};
        *result = atoi(str);
        return true;
    }
    return false;
}

/*void mostrarPilha(Pilha* p) {
    Node* atual = p->topo;
    printf("Topo ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->valor;
    }
    printf("Base\n");
}*/
//arquivo Natanael, resolvendo RPN
double resolveRPN(char *expressao) {
    //char input[100];
    char input_copy[100];
    char *token;
    double num1, num2, result;

    Pilha *prato = criar_pilha();

    /*printf("Digite a expressC#o RPN: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    //printf("tamanho da entrada: %d.\n", strlen(input));
    strcpy(input_copy, input);*/
    // Copia a expressão para uma cópia mutável, pois strtok modifica a string.
    // Garanta que input_copy tenha espaço suficiente.
    if (strlen(expressao) >= sizeof(input_copy)) {
        printf("Erro: Expressao muito longa!\n");
        liberarPilha2(prato);
        return NAN;
    }
    strcpy(input_copy, expressao);

    token = strtok(input_copy, " ");
    //printf("tamanho da copia: %d.\n", strlen(input));
    //while(tamanhoPilha(prato) != 1) {
    while (token) {
        char *fim;
        double val = strtod(token, &fim);
        if (*fim == '\0') {
            empilhar(prato, val); //atof(token) parsing desnecessário visto que strtod já converte
            printf("Empilhando o valor %.2f\n", val);
        }
        /*if (isdigit(token[0])) {
            empilhar(prato, atof(token));
        }*/
        else {
            char operacoesSimples[5] = {'+', '-', '*', '/', '^'};
            bool operacao_binaria = false;
            for (int i = 0; i < 5; i++) {
                if (token[0] == operacoesSimples[i] && token[1] == '\0') {
                    // token[1] == '\0' garante que o token tem só 1 caractere, tipo "+"
                    operacao_binaria = true;
                    break;
                }
            }
            if (operacao_binaria) {
                printf("DEBUG: Tamanho da pilha antes de desempilhar: %d\n", prato->tamanho);
                num1 = desempilhar(prato);
                printf("DEBUG: Tamanho da pilha depois do primeiro desempilhar: %d\n", prato->tamanho);
                num2 = desempilhar(prato);
                printf("DEBUG: Tamanho da pilha depois do segundo desempilhar: %d\n", prato->tamanho);

                switch ((char) token[0]) {
                    case '+':
                        result = num2 + num1;
                        printf("DEBUG: %.2f + %.2f = %.2f\n", num2, num1, result);
                        break;
                    case '-':
                        result = num2 - num1;
                        printf("DEBUG: %.2f - %.2f = %.2f\n", num2, num1, result);
                        break;
                    case '*':
                        result = num2 * num1;
                        printf("DEBUG: %.2f * %.2f = %.2f\n", num2, num1, result);
                        break;
                    case '/':
                        if (num1 == 0) {
                            printf("Erro: Divisao por zero!\n");
                            //destruir_pilha(prato);
                            return NAN; // Retorna NAN para erro
                        }
                        result = num2 / num1;
                        printf("DEBUG: %.2f / %.2f = %.2f\n", num2, num1, result);
                        break;
                    case '^': //potenciação
                        result = pow(num2, num1);
                        printf("DEBUG: %.2f ^ %.2f = %.2f\n", num2, num1, result);
                        break;
                }
                empilhar(prato, result);
            } else {
                double unico = desempilhar(prato);
                if (strcmp(token, "cos") == 0) {
                    result = cos(unico);
                    printf("DEBUG: cos(%.2f) = %.2f\n", unico, result);
                } else if (strcmp(token, "sen") == 0) {
                    result = sin(unico);
                    printf("DEBUG: sin(%.2f) = %.2f\n", unico, result);
                } else if (strcmp(token, "log") == 0) {
                    if (unico <= 0) {
                        printf("Erro: Log de número <= 0!\n");
                        return NAN;
                    }
                    result = log(unico); // log natural (base e)
                    printf("DEBUG: log(%.2f) = %.2f\n", unico, result);
                } else if (strcmp(token, "sqrt") == 0) {
                    if (unico < 0) {
                        printf("Erro: Raiz de número negativo!\n");
                        return NAN;
                    }
                    result = sqrt(unico);
                    printf("DEBUG: sqrt(%.2f) = %.2f\n", unico, result);
                } else {
                    printf("Erro: Funcao desconhecida '%s'\n", token);
                    return NAN;
                }
            }
            //printf("DEBUG: Resultado da operacao %g %c %g = %g\n", num2, token[0], num1, result);
            // Opcional para depuração
            printf("Resultado empilhado:\t%.2f\n", result);
            empilhar(prato, result);
        }


        token = strtok(NULL, " ");
    }
    printf("Operacao:\t%s\nResultado:\t %.2f.", expressao, consultarTopo(prato));
    //}
    double finalResult = consultarTopo(prato);
    return finalResult;
}
