//
// Created by natan on 19/06/2025.
//

#ifndef CONVERTEIN_POSFIXA_H
#define CONVERTEIN_POSFIXA_H

#include "struct_and_utils.h"

void inicializarPilha(PilhaCar *pilha);
void liberarPilha(PilhaCar *pilha);
void empilharCaractere(PilhaCar *pilha, char caractere);
char desempilharCaractere(PilhaCar *pilha);
int obterPrioridade(char operador);
void imprimirExpressao(char *expressao);
char *lerExpressaoDinamica();
char* recebe_infixa();

#endif //CONVERTEIN_POSFIXA_H
