/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Módulo Concorrente utilizando Threads. O processamento da matriz é dividido entre as threads objetivando obter ganho de performance através da concorrência e, principalmente, do paralelismo. */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include "threads.h"
#include "tarefa.h"
#include "utilidades.h"

#define DEBUG 0


/* Variáveis globais */
Resultado* resultadoFinal;
Tarefas* tarefas;
sem_t semaphore;


pthread_t *alocaVetorThreads(int n){
	pthread_t* vet = calloc(n, sizeof(pthread_t));

	if (vet == NULL) {
		printf ("Erro de alocacao de memoria do vetor de threads.");
		return NULL;
	}

	return vet;
}

void* processaMatriz(void *threadId) {
	int tid = (int)threadId;
	if (DEBUG) printf("Executando código da Thread %d...\n", tid);

	Resultado* resultado = executaTarefa(&tarefas[tid]);	
	if (DEBUG) printf("Thread %d: Executei Tarefas de %d a %d...\n", tid, tarefas[tid].inicio, tarefas[tid].fim);


	sem_wait(&semaphore);

	if (DEBUG) printf("Thread %d: Estrei na SC...\n", tid);

	resultadoFinal->mediaPI += resultado->mediaPI;
	resultadoFinal->mediaQuadradoPI += resultado->mediaQuadradoPI;
	resultadoFinal->maiorPI = (resultadoFinal->maiorPI > resultado->maiorPI) ? resultadoFinal->maiorPI : resultado->maiorPI;
	resultadoFinal->menorPI = (resultadoFinal->menorPI < resultado->menorPI) ? resultadoFinal->menorPI : resultado->menorPI;
	resultadoFinal->maiorElem = (resultadoFinal->maiorElem > resultado->maiorElem) ? resultadoFinal->maiorElem : resultado->maiorElem;
	resultadoFinal->menorElem = (resultadoFinal->menorElem < resultado->menorElem) ? resultadoFinal->menorElem : resultado->menorElem;

	if (DEBUG) printf("tid=%d, maiorElem=%d, menorElem=%d, maiorPI=%llu, menorPI=%llu, mediaPI = %.4f, mediaQuadradoPI = %.4f\n", tid, resultadoFinal->maiorElem, resultadoFinal->menorElem, resultadoFinal->maiorPI, resultadoFinal->menorPI, resultadoFinal->mediaPI, resultadoFinal->mediaQuadradoPI);

	sem_post(&semaphore);

	if (DEBUG) printf("Thread %d: Saí da SC...\n", tid);
	
	free(resultado);
}

Resultado* threads(int nThreads, int k) {
	if (DEBUG) puts("Início do módulo de Threads...");
	
	int t;
	tarefas = divideTarefas(nThreads);

	resultadoFinal = (Resultado*)malloc(sizeof(Resultado));
	resultadoFinal->PI = (unsigned long long int*)malloc(k * sizeof(unsigned long long int));
	resultadoFinal->mediaPI = 0.0;
	resultadoFinal->mediaQuadradoPI = 0.0;
	resultadoFinal->maiorPI = getMinimumInt();
	resultadoFinal->menorPI = getMaximumInt();
	resultadoFinal->maiorElem = getMinimumInt();
	resultadoFinal->menorElem = getMaximumInt();


	sem_init(&semaphore, 0, 1);
	pthread_t* threads = alocaVetorThreads(nThreads);

	//Cria e inicia as threads
	for(t=0; t<nThreads; t++) {
		if (pthread_create(&threads[t], NULL, processaMatriz, (void *)t)) {
			printf("ERRO: pthread_create()\n");
			exit(-1);
		}

		if (DEBUG) printf("Thread %d iniciando...\n", t);
	}

	if (DEBUG) puts("Thread Principal: Iniciei todas as Threads");

	//Espera o termino de todas as threads
	for(t=0; t<nThreads; t++) {
		if (pthread_join(threads[t], NULL)) {
			printf("ERRO: pthread_join()\n");
			exit(-1);
		}
	}

	if (DEBUG) puts("Thread Principal: Todas as Threads terminaram...");

	Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
	resultado->PI = (unsigned long long int*)malloc(k * sizeof(unsigned long long int));
	resultado->mediaPI = resultadoFinal->mediaPI;
	resultado->mediaQuadradoPI = resultadoFinal->mediaQuadradoPI;
	resultado->maiorPI = resultadoFinal->maiorPI;
	resultado->menorPI = resultadoFinal->menorPI;
	resultado->maiorElem = resultadoFinal->maiorElem;
	resultado->menorElem = resultadoFinal->menorElem;
	memcpy(resultado->PI, resultadoFinal->PI, k*sizeof(unsigned long long int));


	free(threads);
	free(resultadoFinal->PI);
	free(resultadoFinal);

	if (DEBUG) puts("Encerrando módulo de Threads...");

	return resultado;
}
