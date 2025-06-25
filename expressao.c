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

//converte de infixa pra pos
//Função para inicializar a pilha vazia
void inicializarPilha(PilhaCar *pilha) {
	pilha->dados = NULL; // Significa que não tem nenhum elemento
	pilha->indiceTopo = -1; // Topo -1 para garantir que realmente esteja vazia
}

void inicializarPilhaString(PilhaStr *pilha) {
	pilha->topo = -1; // Topo -1 para garantir que realmente esteja vazia
}

// Função para liberar a memória alocada que foi alocada para a pilha

void liberarPilha(PilhaCar *pilha) {
	free(pilha->dados); // Libera a memória
}

// Função para empilhar cada caractere no topo (com realloc a cada inserção)
// ------------------------------
void empilharCaractere(PilhaCar *pilha, char caractere) {
	char *novo = realloc(pilha->dados, (pilha->indiceTopo + 2) * sizeof(char)); // Realoca para caber mais um caractere
	if (!novo) {
		fprintf(stderr, "Erro ao alocar memória para a pilha.\n");
		exit(EXIT_FAILURE); // Sai do programa caso de erro, pois e uma função da stdlib e serve para
	} //operações impossíveis de continuar como pilha nula ou ponteiro inválido.
	pilha->dados = novo; // Atualiza o ponteiro da pilha
	pilha->dados[++(pilha->indiceTopo)] = caractere; // Incrementa o topo e armazena o elemento no topo da pilha.
}

//Empilha uma string na pilha
void empilharString(PilhaStr *spilha, const char *str) {
	if (spilha->topo >= 99) { //99 pois é o tamanho máximo 100 - 1
		printf("Deu stack overflow\n");
		return -1; // Ta cheio a pilha
	}
	spilha->string[++spilha->topo] = strdup(str); // Duplicate the string and push it
}

// Função para desempilha o elemento do topo e o retornar
char desempilharCaractere(PilhaCar *pilha) {
	if (pilha->indiceTopo >= 0) {
		return pilha->dados[(pilha->indiceTopo)--]; // Retorna o elemento do topo antes da varivel ser diminuida
	} // esse menos menos e para isso se colocar -1 da ruim não me pergunte o porque
	return '\0'; // Se a pilha estiver vazia, retorna 0
}

char* desempilharString(PilhaStr *spilha) {
	return spilha->string[spilha->topo--]; // Return the top string and decrement the top
}

// Retorna a prioridade de operadores
// ^ > * / > + - (não tem parentes justamente para evitar ambiguidade Aqui, a ordem dos operandos e operadores já define a precedência)

int obterPrioridade(char operador) {
	if (operador == '^') return 3;
	if (operador == '*' || operador == '/') return 2;
	if (operador == '+' || operador == '-') return 1;
	return 0; // Qualquer outro caractere não tem prioridade (ou seja numeros e parenteses)
}

// Imprime a expressão

void imprimirExpressao(char *expressao) {
	printf("%s\n", expressao);
}

// Função que faz a leitura da expressão de forma dinâmica, char por char

char *lerExpressaoDinamica() {
	size_t capacidade = 64; // Capacidade inicial para ninguem ficar brincando com o tamanho
	size_t tamanho = 0; // Número de caracteres lidos da expressão
	char *expressao = malloc(capacidade); // Aloca memória inicial (salva a expressão infixa que foi inserida)
	int c; // Caractere atual lido
	
	if (!expressao) {
		fprintf(stderr, "Erro de alocação de memória.\n");
		exit(EXIT_FAILURE); // essa função ja comentei antes
	}
	
	// esse while le o elemento e continua a até a nova linha \n
	while ((c = getchar()) != '\n' && c != EOF) {
		if (tamanho + 1 >= capacidade) {
			// Verifica se já está quase estourando o tamanho do vetor alocado.
			capacidade *= 2; // Se sim dobra a capacidade para realocar mais espaço
			char *temp = realloc(expressao, capacidade); // Esse realloc é para redimensionar
			if (!temp) {
				free(expressao);
				fprintf(stderr, "Erro ao realocar memória.\n");
				exit(EXIT_FAILURE); // já comentei
			}
			expressao = temp;
		}
		expressao[tamanho++] = (char) c; // empilha armazenando o elemento que lido
	}
	
	expressao[tamanho] = '\0'; // Finaliza a string com 0
	return expressao; // Retorna a string lida
}

char *recebe_infixa() {
	char *expressaoInfixa = lerExpressaoDinamica(); // Lê a expressão fornecida
	
	// Aloca espaço para a expressão pós-fixa dobro do tamanho da infixa por segurança, foi do jeito que deu porque parenteses dá problema
	//char *expressaoPosfixa = malloc(strlen(expressaoInfixa) * 2 + 1);
	char *expressaoPosfixa = calloc(strlen(expressaoInfixa) * 4 + 1, sizeof(char)); // + espaço extra por segurança
	int indiceSaida = 0; //int indiceEntrada, indiceSaida = 0;
	
	// Inicializa a pilha de operadores (/*-+. etc)
	PilhaCar pilhaOperadores;
	inicializarPilha(&pilhaOperadores);
	
	// Percorre a expressão elemento por elemento
	/*for (indiceEntrada = 0; expressaoInfixa[indiceEntrada] != '\0'; indiceEntrada++) {
	char caractereAtual = expressaoInfixa[indiceEntrada];
	
	// // Verifica se o elemento inserido e letra ou numero ou operador
	if ((caractereAtual >= 'A' && caractereAtual <= 'Z') || // Letras maiúsculas
	(caractereAtual >= 'a' && caractereAtual <= 'z') || // Letras minusculas
	(caractereAtual >= '0' && caractereAtual <= '9')) { // Numeros
	expressaoPosfixa[indiceSaida++] = caractereAtual;
	expressaoPosfixa[indiceSaida++] =  ' '; //acrescentando os espaços após cada elemento para delimitar a parte
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
	expressaoPosfixa[indiceSaida++] =  ' '; //acrescentando os espaços após cada elemento para delimitar a parte
	}
	empilharCaractere(&pilhaOperadores, caractereAtual);  // Empilha o operador atual
	}
	// Se for parêntese de fechamento
	else if (caractereAtual == ')') {
	// Desempilha até encontrar o parêntese de abertura
	while (pilhaOperadores.indiceTopo != -1 &&
	pilhaOperadores.dados[pilhaOperadores.indiceTopo] != '(') {
	expressaoPosfixa[indiceSaida++] = desempilharCaractere(&pilhaOperadores);
	expressaoPosfixa[indiceSaida++] =  ' '; //acrescentando os espaços após cada elemento para delimitar a parte
	}
	// Remove também o '(' da pilha
	if (pilhaOperadores.indiceTopo != -1 &&
	pilhaOperadores.dados[pilhaOperadores.indiceTopo] == '(') {
	desempilharCaractere(&pilhaOperadores);
	}
	}
	}*/
	
	int i = 0;
	while (expressaoInfixa[i] != '\0') {
		char c = expressaoInfixa[i];
		
		// Ignora espaços
		if (c == ' ') {
			i++;
			continue;
		}
		
		//Detecta números, inclusive negativos e com ponto decimal troquei "strtol"  "strtod()"
		if ((c >= '0' && c <= '9') || (c == '-' && (i == 0 || expressaoInfixa[i - 1] == '(' || expressaoInfixa[i - 1] == '+' || expressaoInfixa[i - 1] == '-' || expressaoInfixa[i - 1] == '*' || expressaoInfixa[i - 1] == '/' || expressaoInfixa[i - 1] == '^'))) {
			char *endPtr;
			
			//converte o valor da string para valor double
			double valor = strtod(&expressaoInfixa[i], &endPtr);
			
			char buffer[64];
			sprintf(buffer, "%g ", valor); // %g evita zeros desnecessários (ex: 2.500000 ? 2.5)
			strcat(expressaoPosfixa, buffer);
			indiceSaida = strlen(expressaoPosfixa);
			
			i = endPtr - expressaoInfixa;
		}
		
		//Identifica Letra
		else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			expressaoPosfixa[indiceSaida++] = c;
			expressaoPosfixa[indiceSaida++] = ' '; // separador
			i++;
		}
		
		//Identifica Parêntese de abertura
		else if (c == '(') {
			empilharCaractere(&pilhaOperadores, c);
			i++;
		}
		
		//Identifica Parêntese de fechamento
		else if (c == ')') {
			while (pilhaOperadores.indiceTopo != -1 &&
				pilhaOperadores.dados[pilhaOperadores.indiceTopo] != '(') {
				expressaoPosfixa[indiceSaida++] = desempilharCaractere(&pilhaOperadores);
				expressaoPosfixa[indiceSaida++] = ' '; // separador
			}
			desempilharCaractere(&pilhaOperadores); // Remove o '('
			i++;
		}
		
		//Identifica os numeros
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
			while (pilhaOperadores.indiceTopo != -1 &&
				obterPrioridade(pilhaOperadores.dados[pilhaOperadores.indiceTopo]) >= obterPrioridade(c)) {
				expressaoPosfixa[indiceSaida++] = desempilharCaractere(&pilhaOperadores);
				expressaoPosfixa[indiceSaida++] = ' '; // separador
			}
			empilharCaractere(&pilhaOperadores, c);
			i++;
		} else {
			i++; // Caracteres inválidos são ignorados
		}
	}
	
	
	// Após o fim da expressão, desempilha tudo que restou
	while (pilhaOperadores.indiceTopo != -1) {
		expressaoPosfixa[indiceSaida++] = desempilharCaractere(&pilhaOperadores);
		expressaoPosfixa[indiceSaida++] = ' '; //acrescentando os espaços após cada elemento para delimitar a parte
	}
	
	expressaoPosfixa[indiceSaida] = '\0'; // Termina a string com zero
	
	// Imprime a expressão original e a convertida
	printf("Expressao Infixa: ");
	imprimirExpressao(expressaoInfixa);
	
	printf("Expressao Posfixa: ");
	imprimirExpressao(expressaoPosfixa);
	
	// Libera memória alocada
	liberarPilha(&pilhaOperadores);
	free(expressaoInfixa);
	//free(expressaoPosfixa);
	
	return expressaoPosfixa; //retornando a expressão corrigida para então usar na resolução da expressão que fiz
}

//Recebe expressão pós-fixada e devolve expressão infixada

char* recebe_posfixa(char* expressaoPosfixa){
	PilhaStr pilha; 
	inicializarPilhaString(&pilha);
	
	for (int i = 0; expressaoPosfixa[i] != '\0'; ) {
		
		if (expressaoPosfixa[i] == ' ') {
			i++;
			continue;
		}
		
		// função da ctype "isdigit()" checa pra ver se é um digito de 0-9 , também checa por possíveis '-' ou '.' pra ver se é de ponto flutuante
		if (isdigit(expressaoPosfixa[i]) || 
			(expressaoPosfixa[i] == '-' && isdigit(expressaoPosfixa[i+1])) || 
			(expressaoPosfixa[i] == '.' && isdigit(expressaoPosfixa[i+1]))) {
			
			char *start = &expressaoPosfixa[i];
			char *end;
			strtod(start, &end); //vai até o final do número identificado
			
			int len = end - start; // mede o tamanho do número em caracteres
			char *num = malloc(len + 1);
			strncpy(num, start, len);
			num[len] = '\0';
			
			empilharString(&pilha, num);
			//mensagem de debug opcional
			//printf("numero empilhado: %s\n", num);
			
			i += len; // move o i pra o tamanho do número, se o número for 4.6 por exemplo , move 3 espaços
		} else {
			//essa parte monta a equação infixada entre parênteses
			char *dir = desempilharString(&pilha);
			char *esq = desempilharString(&pilha);
			
			//alloca memória igual a os parenteses e os numeros
			char *expr = malloc(strlen(esq) + strlen(dir) + 4);
			sprintf(expr, "(%s%c%s)", esq, expressaoPosfixa[i], dir);
			
			free(esq);
			free(dir);
			
			//mensagem de debug opcional
			//printf("expressao empilhada: %s\n", expr);
			
			//devolve a string montada pra pilha
			empilharString(&pilha, expr);
			
			i++; 
		}
	}
	
	
	char *resultado = desempilharString(&pilha);
	return resultado;
}
