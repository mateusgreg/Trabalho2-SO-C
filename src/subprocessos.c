/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Módulo Concorrente utilizando Subprocessos. O processamento da matriz é dividido entre os subprocessos objetivando obter ganho de performance através da concorrência e, principalmente, do paralelismo. */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "subprocessos.h"
#include "utilidades.h"
#include "tarefa.h"

#define SHARED_NAME_RESULTADO "/sharedResultado"
#define SHARED_NAME_PI "/sharedPI"
#define SHARED_NAME_TAREFAS "/sharedTarefas"
#define SEM_NAME "/semaphore"
#define SEM_INIT_VALUE 1

#define DEBUG 0


/* Variáveis globais */
Resultado* resultadoFinal;
Tarefas* tarefas;
sem_t* semaphore;


Resultado* subprocessos(int nSubprocessos, int k){
	int i;
	int pid;
	int shmfdResultado;
	int sharedSegSizeResultado = 1 * sizeof(Resultado);
	int shmfdPI;
	int sharedSegSizePI = k * sizeof(unsigned long long int);
	int shmfdTarefas;
	int sharedSegSizeTarefas = nSubprocessos * sizeof(Tarefas);

	Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
	resultado->PI = (unsigned long long int*)malloc(k * sizeof(unsigned long long int));


	/* Struct que armazena os resultados do processamento da matriz */
	shmfdResultado = shm_open(SHARED_NAME_RESULTADO, O_CREAT | O_RDWR, 0666);
	if (shmfdResultado == -1){
		printf("Erro shm_open Resultado aborting...\n");
		exit(-1);
	}

	if(ftruncate(shmfdResultado, sharedSegSizeResultado) == -1){
		printf("error truncating Resultado\n");
		exit(-1);
	}

	resultadoFinal = mmap(NULL, sharedSegSizeResultado, PROT_READ | PROT_WRITE, MAP_SHARED, shmfdResultado, 0);

	if(resultadoFinal == MAP_FAILED){
		printf("error mapping Resultado\n");
		exit(-1);
	}

	resultadoFinal->mediaPI = 0.0;
	resultadoFinal->mediaQuadradoPI = 0.0;
	resultadoFinal->maiorPI = getMinimumInt();
	resultadoFinal->menorPI = getMaximumInt();
	resultadoFinal->maiorElem = getMinimumInt();
	resultadoFinal->menorElem = getMaximumInt();


	/* Vetor de Produtos Internos */
	shmfdPI = shm_open(SHARED_NAME_PI, O_CREAT | O_RDWR, 0666);
	if (shmfdPI == -1){
		printf("Erro shm_open PI aborting...\n");
		exit(-1);
	}

	if(ftruncate(shmfdPI, sharedSegSizePI) == -1){
		printf("error truncating PI\n");
		exit(-1);
	}

	resultadoFinal->PI = mmap(NULL, sharedSegSizePI, PROT_READ | PROT_WRITE, MAP_SHARED, shmfdPI, 0);

	if(resultadoFinal->PI == MAP_FAILED){
		printf("error mapping PI\n");
		exit(-1);
	}


	/* Vetor de Tarefas */
	shmfdTarefas = shm_open(SHARED_NAME_TAREFAS, O_CREAT | O_RDWR, 0666);
	if (shmfdTarefas == -1){
		printf("Erro shm_open Tarefas aborting...\n");
		exit(-1);
	}

	if(ftruncate(shmfdTarefas, sharedSegSizeTarefas) == -1){
		printf("error truncating Tarefas\n");
		exit(-1);
	}

	tarefas = mmap(NULL, sharedSegSizeTarefas, PROT_READ | PROT_WRITE, MAP_SHARED, shmfdTarefas, 0);

	if(tarefas == MAP_FAILED){
		printf("error mapping Tarefas\n");
		exit(-1);
	}
	
	memcpy(tarefas, divideTarefas(nSubprocessos), sharedSegSizeTarefas);


	/* Inicializando Semáforo */
	semaphore = sem_open(SEM_NAME, O_CREAT, 0666, SEM_INIT_VALUE);
	if(semaphore == SEM_FAILED){
		printf("error sem_open\n");
		exit(-1);
	}


	for(i = 0; i < nSubprocessos; i++){
		pid = fork();
		if(pid < 0){ printf("Erro ao criar subprocessos, abortando...\n"); exit(-1); }
		if(pid == 0){
			executaTarefaSubprocesso(i);
			exit(0);
		}
	}

	if(pid > 0){
		for(i = 0; i < nSubprocessos; i++){
			wait(NULL);
		}

		resultado->mediaPI = resultadoFinal->mediaPI;
		resultado->mediaQuadradoPI = resultadoFinal->mediaQuadradoPI;
		resultado->maiorPI = resultadoFinal->maiorPI;
		resultado->menorPI = resultadoFinal->menorPI;
		resultado->maiorElem = resultadoFinal->maiorElem;
		resultado->menorElem = resultadoFinal->menorElem;

		memcpy(resultado->PI, resultadoFinal->PI, sharedSegSizePI);

		
		/* Encerrando Semáforo */
		if(sem_close(semaphore) != 0){
			printf("error sem_close\n");
			exit(-1);
		}


		/* Unmaping Vetor de Tarefas */
		if((munmap(tarefas, sharedSegSizeTarefas)) != 0){
			printf("error unmap Tarefas\n");
			exit(-1);
		}

		if((shm_unlink(SHARED_NAME_TAREFAS)) != 0){
			printf("error shm_unlink Tarefas\n");
			exit(-1);
		}


		/* Unmaping Vetor de PIs */
		if((munmap(resultadoFinal->PI, sharedSegSizePI)) != 0){
			printf("error unmap PI\n");
			exit(-1);
		}

		if((shm_unlink(SHARED_NAME_PI)) != 0){
			printf("error shm_unlink PI\n");
			exit(-1);
		}


		/* Unmaping Struct de Resultados */
		if((munmap(resultadoFinal, sharedSegSizeResultado)) !=0){
			printf("error unmap Resultado\n");
			exit(-1);
		}

		if((shm_unlink(SHARED_NAME_RESULTADO)) != 0){
			printf("error shm_unlink Resultado\n");
			exit(-1);
		}
	}

	if (DEBUG) printf("\nFim do Módulo de Subprocessos...\n");

	return resultado;
}

void executaTarefaSubprocesso(int meuPidLogico){
	Resultado* resultado;

	/* Cast sem explicacao mas o compilador da warning. falando que tento fazer int em pointer sem cast */
	resultado = (Resultado*)executaTarefa(&tarefas[meuPidLogico]);

	sem_wait(semaphore);

	resultadoFinal->mediaPI += resultado->mediaPI;
	resultadoFinal->mediaQuadradoPI += resultado->mediaQuadradoPI;
	resultadoFinal->maiorPI = (resultadoFinal->maiorPI > resultado->maiorPI) ? resultadoFinal->maiorPI : resultado->maiorPI;
	resultadoFinal->menorPI = (resultadoFinal->menorPI < resultado->menorPI) ? resultadoFinal->menorPI : resultado->menorPI;
	resultadoFinal->maiorElem = (resultadoFinal->maiorElem > resultado->maiorElem) ? resultadoFinal->maiorElem : resultado->maiorElem;
	resultadoFinal->menorElem = (resultadoFinal->menorElem < resultado->menorElem) ? resultadoFinal->menorElem : resultado->menorElem;

	if (DEBUG) printf("meuPidLogico=%d, maiorElem=%d, menorElem=%d, maiorPI=%llu, menorPI=%llu, mediaPI = %.4f, mediaQuadradoPI = %.4f\n", meuPidLogico, resultadoFinal->maiorElem, resultadoFinal->menorElem, resultadoFinal->maiorPI, resultadoFinal->menorPI, resultadoFinal->mediaPI, resultadoFinal->mediaQuadradoPI);

	sem_post(semaphore);

	free(resultado);	
}
