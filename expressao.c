#include "expressao.h";
#include <stdio.h>;
#include <stdbool.h>;

Pilha *criar_pilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha == NULL)
    {
        printf("Erro ao alocar memória para a pilha.\n");
        return NULL;
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

void empilhar(Pilha *pilha, int valor)
{
    Node *novo_node = malloc(sizeof(Node));

    if (!novo_node)
    {
        printf("Falha ao alocar memória para novo node");
        return;
    }

    novo_node->valor = valor;
    novo_node->proximo = pilha->topo;
    pilha->topo = novo_node;
    pilha->tamanho++;
}

int desempilhar(Pilha *pilha)
{

    Node *temp = pilha->topo;
    pilha->topo = temp->proximo;
    int valor = temp->valor;

    free(temp);

    return valor;
}

int peek(Pilha *pilha)
{
    return pilha->topo;
}

int realizarOperacao(int y, int x, char operador)
{
    int resultado;
    switch (operador)
    {
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

int resolverPosFix(Pilha *pilha, char expressao[], int tamanho)
{

    for (int i = 0; i < tamanho; i++)
    {
        int numero;
        if (TryParse(expressao[i], &numero))
        {
            empilhar(pilha, numero);
        }
        else
        {
            int x = desempilhar(pilha);
            int y = desempilhar(pilha);
            int res = realizarOperacao(y, x, expressao[i]);
            empilhar(pilha, res);
        }
    }
}

int potencia(int base, int expoente)
{
    int resultado = 1;
    for (int i = 0; i < expoente; i++)
    {
        resultado *= base;
    }
    return resultado;
}

int radiciacao(int numero)
{
    float raiz = numero / 2;
    float temp = 0;
    while (raiz != temp)
    {
        temp = raiz;
        raiz = (numero / temp + temp) / 2;
    }
    return raiz;
}

int seno(int angulo)
{
    float resultado = angulo;
    float termo = angulo;
    int n = 1;
    for (int i = 1; i <= 10; i++)
    {
        termo *= -1 * angulo * angulo / ((2 * n) * (2 * n + 1));
        resultado += termo;
        n++;
    }
    return resultado;
}

int cosseno(int angulo)
{
    float resultado = 1;
    float termo = 1;
    int n = 1;
    for (int i = 1; i <= 10; i++)
    {
        termo *= -1 * angulo * angulo / ((2 * n - 1) * (2 * n));
        resultado += termo;
        n++;
    }
    return resultado;
}

bool TryParse(char n, int *result)
{
    if (n >= '0' && n <= '9')
    {
        char str[2] = {n, '\0'};
        *result = atoi(str);
        return true;
    }
    return false;
}