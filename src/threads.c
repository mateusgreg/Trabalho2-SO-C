/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Módulo Concorrente utilizando Threads. O processamento da matriz é dividido entre as threads objetivando obter ganho de performance através da concorrência e, principalmente, do paralelismo. */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "threads.h"
#include "tarefa.h"


//variaveis globais
Resultado* resultado;


//aloca espaco em memoria para um vetor do tipo pthread_t de n elementos
pthread_t *alocaVetorThreads(int n){
	pthread_t *vet = calloc(n, sizeof(pthread_t));

	if (vet == NULL) {
		printf ("Erro de alocacao de memoria do vetor de threads.");
		return NULL;
	}

	return vet;
}

void* processaMatriz(void *threadId) {
	int tid = (int)threadId;

	//TODO:executaTarefa(indices, tamVetorIndices);

}

Resultado* threads(int nThreads, int k, int* PIFinal) {

	int //nThreads = k,	//TODO: DEfinir logica para escolher num. de threads
		t,
		indice=0,
		quociente = k/nThreads,
		resto = k % nThreads;

	pthread_t *threads;
	//TODO:Criar semáforos

	//TODO:Inicializar Semáforos
	threads = alocaVetorThreads(nThreads);

	//Cria as threads
	for(t=0; t<nThreads; t++) {
		if (pthread_create(&threads[t], NULL, processaMatriz, (void *)t)) {
			printf("--ERRO: pthread_create()\n");
			exit(-1);
		}
	}

	//Espera o termino de todas as threads
	for(t=0; t<nThreads; t++) {
		if (pthread_join(threads[t], NULL)) {
			printf("--ERRO: pthread_join() \n");
			exit(-1);
		}
	}

	return resultado;
}
