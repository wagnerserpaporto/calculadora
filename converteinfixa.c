#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da pilha

typedef struct {
    char *dados;       // Vetor dinâmico para armazenar os caracteres empilhados
    int indiceTopo;    // Índice do topo da pilha (última posição com elemento válido)
} PilhaCar;

//Função para inicializar a pilha vazia

void inicializarPilha(PilhaCar *pilha) {
    pilha->dados = NULL;       // Significa que não tem nenhum elemento
    pilha->indiceTopo = -1;    // Topo -1 para garantir que realmente esteja vazia
}

// Função para liberar a memória alocada que foi alocada para a pilha

void liberarPilha(PilhaCar *pilha) {
    free(pilha->dados);        // Libera a memória
}

// Função para empilhar cada caractere no topo (com realloc a cada inserção)
// ------------------------------
void empilharCaractere(PilhaCar *pilha, char caractere) {
    char *novo = realloc(pilha->dados, (pilha->indiceTopo + 2) * sizeof(char));// Realoca para caber mais um caractere
    if (!novo) {
        fprintf(stderr, "Erro ao alocar memória para a pilha.\n");
        exit(EXIT_FAILURE);  // Sai do programa caso de erro, pois e uma função da stdlib e serve para
    }                         //operações impossíveis de continuar como pilha nula ou ponteiro inválido.
    pilha->dados = novo;                         // Atualiza o ponteiro da pilha
    pilha->dados[++(pilha->indiceTopo)] = caractere;  // Incrementa o topo e armazena o elemento no topo da pilha.
}

// Função para desempilha o elemento do topo e o retornar

char desempilharCaractere(PilhaCar *pilha) {
    if (pilha->indiceTopo >= 0) {
        return pilha->dados[(pilha->indiceTopo)--];  // Retorna o elemento do topo antes da varivel ser diminuida
    }                                                 // esse menos menos e para isso se colocar -1 da ruim não me pergunte o porque
    return '\0';  // Se a pilha estiver vazia, retorna 0
}

// Retorna a prioridade de operadores
// ^ > * / > + - (não tem parentes justamente para evitar ambiguidade Aqui, a ordem dos operandos e operadores já define a precedência)

int obterPrioridade(char operador) {
    if (operador == '^') return 3;
    if (operador == '*' || operador == '/') return 2;
    if (operador == '+' || operador == '-') return 1;
    return 0;  // Qualquer outro caractere não tem prioridade (ou seja numeros e parenteses)
}

// Imprime a expressão

void imprimirExpressao(char *expressao) {
    printf("%s\n", expressao);
}

// Função que faz a leitura da expressão de forma dinâmica, char por char

char *lerExpressaoDinamica() {
    size_t capacidade = 64;                // Capacidade inicial para ninguem ficar brincando com o tamanho
    size_t tamanho = 0;                    // Número de caracteres lidos da expressão
    char *expressao = malloc(capacidade);  // Aloca memória inicial (salva a expressão infixa que foi inserida)
    int c;                                 // Caractere atual lido

    if (!expressao) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);  // essa função ja comentei antes
    }

    // esse while le o elemento e continua a até a nova linha \n
    while ((c = getchar()) != '\n' && c != EOF) {
        if (tamanho + 1 >= capacidade) { // Verifica se já está quase estourando o tamanho do vetor alocado.
            capacidade *= 2;             // Se sim dobra a capacidade para realocar mais espaço
            char *temp = realloc(expressao, capacidade); // Esse realloc é para redimensionar
            if (!temp) {
                free(expressao);
                fprintf(stderr, "Erro ao realocar memória.\n");
                exit(EXIT_FAILURE); // já comentei
            }
            expressao = temp;
        }
        expressao[tamanho++] = (char)c;  // empilha armazenando o elemento que lido
    }

    expressao[tamanho] = '\0';  // Finaliza a string com 0
    return expressao;           // Retorna a string lida
}

int main() {
    printf("Digite a Expressao Infixa: ");
    char *expressaoInfixa = lerExpressaoDinamica();  // Lê a expressão fornecida

    // Aloca espaço para a expressão pós-fixa dobro do tamanho da infixa por segurança, foi do jeito que deu porque parenteses da problema
    char *expressaoPosfixa = malloc(strlen(expressaoInfixa) * 2 + 1);
    int indiceEntrada, indiceSaida = 0;

    // Inicializa a pilha de operadores (/*-+. etc)
    PilhaCar pilhaOperadores;
    inicializarPilha(&pilhaOperadores);

    // Percorre a expressão elemento por elemento
    for (indiceEntrada = 0; expressaoInfixa[indiceEntrada] != '\0'; indiceEntrada++) {
        char caractereAtual = expressaoInfixa[indiceEntrada];

        // // Verifica se o elemento inserido e letra ou numero ou operador
        if ((caractereAtual >= 'A' && caractereAtual <= 'Z') || // Letras maiúsculas
            (caractereAtual >= 'a' && caractereAtual <= 'z') || // Letras minusculas
            (caractereAtual >= '0' && caractereAtual <= '9')) { // Numeros
            expressaoPosfixa[indiceSaida++] = caractereAtual;
        }
        // Se for parêntese de abertura empilha
        else if (caractereAtual == '(') {
            empilharCaractere(&pilhaOperadores, caractereAtual);
        }
        // Se for operador (+, -, *, /, ^)
        //antes de empilhar esse novo operador deve se garantir que nenhum operador de prioridade maior ou igual
        //esteja no topo da pilha se tiver, ele deve ser desempilhado e enviado para o topo primeiro.
        else if (caractereAtual == '+' || caractereAtual == '-' ||
                 caractereAtual == '*' || caractereAtual == '/' ||
                 caractereAtual == '^') {
            while (pilhaOperadores.indiceTopo != -1 &&
                   obterPrioridade(pilhaOperadores.dados[pilhaOperadores.indiceTopo]) >= obterPrioridade(caractereAtual)) {
                expressaoPosfixa[indiceSaida++] = desempilharCaractere(&pilhaOperadores);
            }
            empilharCaractere(&pilhaOperadores, caractereAtual);  // Empilha o operador atual
        }
        // Se for parêntese de fechamento
        else if (caractereAtual == ')') {
            // Desempilha até encontrar o parêntese de abertura
            while (pilhaOperadores.indiceTopo != -1 &&
                   pilhaOperadores.dados[pilhaOperadores.indiceTopo] != '(') {
                expressaoPosfixa[indiceSaida++] = desempilharCaractere(&pilhaOperadores);
            }
            // Remove também o '(' da pilha
            if (pilhaOperadores.indiceTopo != -1 &&
                pilhaOperadores.dados[pilhaOperadores.indiceTopo] == '(') {
                desempilharCaractere(&pilhaOperadores);
            }
        }
    }

    // Após o fim da expressão, desempilha tudo que restou
    while (pilhaOperadores.indiceTopo != -1) {
        expressaoPosfixa[indiceSaida++] = desempilharCaractere(&pilhaOperadores);
    }

    expressaoPosfixa[indiceSaida] = '\0';  // Termina a string com zero

    // Imprime a expressão original e a convertida
    printf("Expressao Infixa: ");
    imprimirExpressao(expressaoInfixa);

    printf("Expressao Posfixa: ");
    imprimirExpressao(expressaoPosfixa);

    // Libera memória alocada
    liberarPilha(&pilhaOperadores);
    free(expressaoInfixa);
    free(expressaoPosfixa);

    return 0;
}

