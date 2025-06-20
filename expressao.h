#include <stdbool.h>

#include "struct_and_utils.h"

#ifndef EXPRESSAO_H
#define EXPRESSAO_H

Pilha *criar_pilha();
void empilhar(Pilha *pilha, double valor);
double desempilhar(Pilha *pilha);

double consultarTopo(Pilha* pilha); //int peek(Pilha *pilha);
int estaVazia(Pilha* pilha);
int tamanhoPilha(Pilha* pilha);
void liberarPilha2(Pilha* p);

int realizarOperacao(int y, int x, char operador);
int potencia(int base, int expoente);
int radiciacao(int numero);
int seno(int angulo);
int cosseno(int angulo);
int resolverPosFix(Pilha *pilha, char expressao[]);
bool TryParse(char n, int *result);
double resolveRPN(char* expressao);
#endif