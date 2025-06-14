#include <stdbool.h>;

#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct pilha
{
    Node *topo;
    int tamanho;
} Pilha;

typedef struct node
{
    int *valor;
    Node *proximo;
} Node;

Pilha *criar_pilha();
void empilhar(Pilha *pilha, int valor);
int desempilhar(Pilha *pilha);
int peek(Pilha *pilha);
int realizarOperacao(int y, int x, char operador);
int potencia(int base, int expoente);
int radiciacao(int numero);
int seno(int angulo);
int cosseno(int angulo);
int resolverPosFix(Pilha *pilha, char expressao[], int tamanho);
bool TryParse(char n, int *result);
#endif