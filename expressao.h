#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI 3.1415

#ifndef EXPRESSAO_H
#define EXPRESSAO_H

//structs e utilidades
// Estrutura da pilha
typedef struct {
	char* dados; // Vetor dinâmico para armazenar os caracteres empilhados
	int indiceTopo; // Índice do topo da pilha (última posição com elemento válido)
} PilhaCar;

// decidi manter uma pilha de strings , não consegui fazer usando a PilhaCar
typedef struct {
	char* string[100]; // Vetor dinâmico para armazenar as strings empilhadas , 100 é o numero máximo de strings que podem ser armazenadas
	int topo; // Índice do topo da pilha (última posição com elemento válido)
} PilhaStr;


typedef struct node {
	double valor; //int  *valor
	struct Node* proximo;
} Node;

typedef struct pilha {
	Node *topo;
	int tamanho;
} Pilha;

//operações de processamento de numeros e as pilhas
Pilha *criar_pilha();
void empilhar(Pilha *pilha, double valor);
double desempilhar(Pilha *pilha);


void inicializarPilha(PilhaCar *pilha);  
void inicializarPilhaString(PilhaStr *pilha);
void liberarPilha(PilhaCar *pilha); 
double consultarTopo(Pilha* pilha); //int peek(Pilha *pilha);
int estaVazia(Pilha* pilha);
int tamanhoPilha(Pilha* pilha);
void liberarPilha2(Pilha* p);
void empilharCaractere(PilhaCar *pilha, char caractere);
void empilharString(PilhaStr *pilha, const char *str);
char desempilharCaractere(PilhaCar *pilha);

int realizarOperacao(int y, int x, char operador);
int potencia(int base, int expoente);
int radiciacao(int numero);
int seno(int angulo);
int cosseno(int angulo);
int resolverPosFix(Pilha *pilha, char expressao[]);
bool TryParse(char n, int *result);
double resolveRPN(char* expressao);

//converte de infixada pra pós-fixada


int obterPrioridade(char operador);
void imprimirExpressao(char *expressao);
char *lerExpressaoDinamica();
char* recebe_infixa();

//converte de pós-fixada pra infixada

char* recebe_posfixa(char* expressaoPosfixa);
#endif
