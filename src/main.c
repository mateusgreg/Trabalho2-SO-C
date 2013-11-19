/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa principal, responsável por interfacear com o usuário através da Console. Obtém os dados da entrada padrão (teclado) e redireciona o processamento da matriz gerada para o módulo correspondente. */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "matriz.h"
#include "resultado.h"
#include "sequencial.h"
#include "subprocessos.h"
#include "threads.h"


/* Variáveis globais */
int k;
int** matrizGerada;


double tempoEmMilisegundos(struct timeval tInicial, struct timeval tFinal) {
	double tempo;

	tempo = (long long)(tFinal.tv_sec - tInicial.tv_sec) * 1000.0 +	   // segundos para milisegundos
		(long long)(tFinal.tv_usec - tInicial.tv_usec) / 1000.0;   // microsegundos para milisegundos

	return tempo;
}

double tempoEmMicrosegundos(struct timeval tInicial, struct timeval tFinal) {
	double tempo;

	tempo = (long long)(tFinal.tv_sec - tInicial.tv_sec) * 1000000.0 +    // segundos para microsegundos
		(long long)(tFinal.tv_usec - tInicial.tv_usec);   	      // microsegundos

	return tempo;
}

void printResultadoConsole(Resultado* resultado) {
	int i;

	printf("\n===============\n");
	printf(" **RESULTADO** ");
	printf("\n===============\n\n");

	printf("Menor Elemento da Matriz: %d\n", resultado->menorElem);
	printf("Maior Elemento da Matriz: %d\n", resultado->maiorElem);

	printf("\nVetor de Produtos Internos:\n[ ");
	for(i=0; i<k-1; i++) {
		printf("%d, ", resultado->PI[i]);
	}
	printf("%d ]\n", resultado->PI[i]);

	printf("\nMenor Produto Interno: %d\n", resultado->menorPI);
	printf("Maior Produto Interno: %d\n", resultado->maiorPI);
	printf("Valor Médio dos Produtos Internos: %.4f\n", resultado->mediaPI);
	printf("Média dos Quadrados dos Produtos Internos: %.4f\n", resultado->mediaQuadradoPI);
	printf("Desvio Padrão dos Produtos Internos: %.4f\n", sqrt(resultado->mediaQuadradoPI - pow(resultado->mediaPI, 2)) );

	if (resultado->tempoEmMilis == 0) {
		printf("Tempo de processamento: %.4f microsegundos\n\n", resultado->tempoEmMicros);
	} else {
		printf("Tempo de processamento: %.4f milisegundos\n\n", resultado->tempoEmMilis);
	}
}

void printResultadoFormatoCSV(Resultado* resultado) {
	printf("Menor Elemento da Matriz, Maior Elemento da Matriz, Menor Produto Interno, Maior Produto Interno, ");
	printf("Valor Médio dos Produtos Internos, Média dos Quadrados dos Produtos Internos, Desvio Padrão dos Produtos Internos, Tempo de Execução (em Microsegundos)");
	printf("\n");
	
	printf("%d, %d, %d, %d, ", resultado->menorElem, resultado->maiorElem, resultado->menorPI, resultado->maiorPI);
	printf("%.4f, %.4f, %.4f, %.4f", resultado->mediaPI, resultado->mediaQuadradoPI, sqrt(resultado->mediaQuadradoPI - pow(resultado->mediaPI, 2)), resultado->tempoEmMicros);
	printf("\n");
}

int main(int argc, char* argv[]) {

	int opcao, invalido, undExecucao;
	Resultado* resultado;
	
	struct timeval tInicial, tFinal;

	while (1) {
		printf("\n============\n");
		printf(" **INÍCIO** ");
		printf("\n============\n");
		
		printf("\nDigite a dimensão da matriz a ser gerada: ");
		scanf("%d", &k);

		if (k == 0) break;

		matrizGerada = geraMatriz(k);

		do {
			printf("\nDe que maneira você deseja fazer os cálculos da matriz gerada:\n");
			printf("1. Sequencial\n");
			printf("2. Subprocessos\n");
			printf("3. Threads\n");

			printf("\nOpção: ");
			scanf("%d", &opcao);

			switch(opcao) {
			case 1:
    				gettimeofday(&tInicial, NULL);	// start timer
				resultado = sequencial(k);
				gettimeofday(&tFinal, NULL);	// stop timer

				resultado->tempoEmMilis = tempoEmMilisegundos(tInicial, tFinal);
				resultado->tempoEmMicros = tempoEmMicrosegundos(tInicial, tFinal);

				invalido = 0;
				break;
			case 2:
				printf("Quantos subprocessos você deseja utilizar no processamento da matriz?\n");
				scanf("%d", &undExecucao);
				
				gettimeofday(&tInicial, NULL);	// start timer
				resultado = subprocessos(undExecucao, k);
				gettimeofday(&tFinal, NULL);	// stop timer

				resultado->tempoEmMilis = tempoEmMilisegundos(tInicial, tFinal);
				resultado->tempoEmMicros = tempoEmMicrosegundos(tInicial, tFinal);

				invalido = 0;
				break;
			case 3:
				printf("Quantas threads você deseja utilizar no processamento da matriz?\n");
				scanf("%d", &undExecucao);

				gettimeofday(&tInicial, NULL);	// start timer
				resultado = threads(undExecucao, k);
				gettimeofday(&tFinal, NULL);	// stop timer
				
				resultado->tempoEmMilis = tempoEmMilisegundos(tInicial, tFinal);
				resultado->tempoEmMicros = tempoEmMicrosegundos(tInicial, tFinal);

				invalido = 0;
				break;
			default:
				printf("\nOpção inválida! Tente novamente...\n");
				invalido = 1;
			}
		}while (invalido);
		

		printResultadoConsole(resultado);
		//printResultadoFormatoCSV(resultado);
	}

	return 0;
}
