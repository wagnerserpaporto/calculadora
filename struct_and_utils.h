//
// Created by natan on 19/06/2025.
//

#ifndef STRUCT_AND_UTILS_H
#define STRUCT_AND_UTILS_H

#include <stdlib.h>
#include <math.h>

// Estrutura da pilha
typedef struct {
    char *dados; // Vetor dinâmico para armazenar os caracteres empilhados
    int indiceTopo; // Índice do topo da pilha (última posição com elemento válido)
} PilhaCar;

typedef struct node {
    double valor; //int  *valor
    struct Node* proximo;
} Node;

typedef struct pilha {
    Node *topo;
    int tamanho;
} Pilha;


#endif //STRUCT_AND_UTILS_H
