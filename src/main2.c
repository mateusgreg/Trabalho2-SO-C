/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o parâmetro informado em tempo de execução */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriz.h"
#include "resultado.h"
#include "sequencial.h"
#include "subprocessos.h"
#include "threads.h"


//variáveis globais
int k = 1;
int** matrizGerada;
int* PI;


void printResultadoConsole(Resultado* resultado) {
	int i;

	printf("Menor Elemento da Matriz: %d\n", resultado->menorElem);
	printf("Maior Elemento da Matriz: %d\n", resultado->maiorElem);

	printf("\nVetor de Produtos Internos:\n[ ");
	for(i=0; i<k; i++) {
		printf("%d ", PI[i]);
	}
	printf("]\n");

	printf("Menor Produto Interno: %d\n", resultado->menorPI);
	printf("Maior Produto Interno: %d\n", resultado->maiorPI);
	printf("Valor Médio dos Produtos Internos: %.4f\n", resultado->mediaPI);
	printf("Média dos Quadrados dos Produtos Internos: %.4f\n", resultado->mediaQuadradoPI);
	printf("Desvio Padrão dos Produtos Internos: %.4f\n", sqrt(resultado->mediaQuadradoPI - pow(resultado->mediaPI, 2)) );
}

void printResultadoFormatoCSV(Resultado* resultado) {
	printf("Menor Elemento da Matriz, Maior Elemento da Matriz, Menor Produto Interno, Maior Produto Interno,
			Valor Médio dos Produtos Internos, Média dos Quadrados dos Produtos Internos, Desvio Padrão dos Produtos Internos");
	
	printf("\n");
	
	printf("%d, %d, %d, %d, %.4f, %.4f, %.4f", resultado->menorElem, resultado->maiorElem, resultado->menorPI, resultado->maiorPI,
			resultado->mediaPI, resultado->mediaQuadradoPI, sqrt(resultado->mediaQuadradoPI - pow(resultado->mediaPI, 2)));
}

int main(int argc, char* argv[]) {

	int opcao, invalido, undExecucao;
	Resultado* resultado;

	while (k) {
		printf("Digite a dimensão da matriz: ");
		scanf("%d", &k);

		matrizGerada = geraMatriz(k);

		do {
			printf("De que maneira você deseja fazer os cálculos da matriz gerada:\n");
			printf("1. Sequencial\n");
			printf("2. Subprocessos\n");
			printf("3. Threads\n");

			printf("\nOpção: ");
			scanf("%d", &opcao);

			switch(opcao) {
			case 1:
				resultado = sequencial(k, PI);
				break;
			case 2:
				printf("Quantos subprocessos você deseja utilizar no proessamento da matriz?\n");
				scanf("%d", &undExecucao);

				resultado = executaSubprocessos(undExecucao, k, PI);
				break;
			case 3:
				printf("Quantos subprocessos você deseja utilizar no proessamento da matriz?\n");
				scanf("%d", &undExecucao);

				resultado = threads(undExecucao, k, PI);
				break;
			default:
				printf("\nERRO: Menu inválido!\n");
				invalido = 1;
			}
		}while (invalido);
		

		printResultadoConsole(resultado);
		//printResultadoFormatoCSV(resultado);
	}

	return 0;
}
