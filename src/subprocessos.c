
#include "subprocessos.h"
#include "utilidades.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHARED_NAME_RESULTADO "/sharedResultado"
#define SHARED_NAME_PI "/sharedPI"
#define SEM_NAME "/semaphore"
#define SEM_INIT_VALUE 1

#define DEBUG 0

Resultado* resultadoFinal;
//int* PI;
sem_t* semaphore;

Resultado* subprocessos(int nsubprocessos, int k, int* PIFinal){
	int i;
	int pid;
	int shmfdResultado;
	int sharedSegSizeResultado = 1 * sizeof(Resultado);
	int shmfdPI;
	int sharedSegSizePI = k * sizeof(int);
	
	Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
	resultado->PI = (int*)malloc(k * sizeof(int));

	shmfdResultado = shm_open(SHARED_NAME_RESULTADO, O_CREAT | O_RDWR, 0666);
	if (shmfdResultado == -1){
		printf("Erro shm_open resultado aborting...\n");
		exit(-1);
	}

	if(ftruncate(shmfdResultado, sharedSegSizeResultado) == -1){
		printf("error truncating resultado\n");
		exit(-1);
	}

	resultadoFinal = mmap(NULL, sharedSegSizeResultado, PROT_READ | PROT_WRITE, MAP_SHARED, shmfdResultado, 0);

	if(resultadoFinal == MAP_FAILED){
		printf("error mapping resultado\n");
		exit(-1);
	}


	shmfdPI = shm_open(SHARED_NAME_PI, O_CREAT | O_RDWR, 0666);
	if (shmfdPI == -1){
		printf("Erro shm_open pi aborting...\n");
		exit(-1);
	}

	if(ftruncate(shmfdPI, sharedSegSizePI) == -1){
		printf("error truncating pi\n");
		exit(-1);
	}

	//PI = mmap(NULL, sharedSegSizePI, PROT_READ | PROT_WRITE, MAP_SHARED, shmfdPI, 0);
	resultadoFinal->PI = mmap(NULL, sharedSegSizePI, PROT_READ | PROT_WRITE, MAP_SHARED, shmfdPI, 0);

	//if(PI == MAP_FAILED){
	if(resultadoFinal->PI == MAP_FAILED){
		printf("error mapping PI\n");
		exit(-1);
	}


	resultadoFinal->mediaPI = 0.0;
	resultadoFinal->mediaQuadradoPI = 0.0;
	resultadoFinal->maiorPI = getMinimumInt();
	resultadoFinal->menorPI = getMaximumInt();
	resultadoFinal->maiorElem = getMinimumInt();
	resultadoFinal->menorElem = getMaximumInt();
	

	semaphore = sem_open(SEM_NAME, O_CREAT, 0666, SEM_INIT_VALUE);
	if(semaphore == SEM_FAILED){
		printf("error sem_open\n");
		exit(-1);
	}

	for(i = 0; i < nsubprocessos; i++){
		pid = fork();
		if(pid < 0){ printf("Erro ao criar subprocessos, abortando...\n"); exit(-1); }
		if(pid == 0){
			executaTarefaSubprocesso(i);
			exit(0);
		}
	}

	if(pid > 0){
		for(i = 0; i < nsubprocessos; i++){
			wait(NULL);
		}

		resultado->mediaPI = resultadoFinal->mediaPI;
		resultado->mediaQuadradoPI = resultadoFinal->mediaQuadradoPI;
		resultado->maiorPI = resultadoFinal->maiorPI;
		resultado->menorPI = resultadoFinal->menorPI;
		resultado->maiorElem = resultadoFinal->maiorElem;
		resultado->menorElem = resultadoFinal->menorElem;

		//memcpy(PIFinal, PI, sharedSegSizePI);
		memcpy(resultado->PI, resultadoFinal->PI, sharedSegSizePI);

		if(sem_close(semaphore) != 0){
			printf("error sem_close\n");
			exit(-1);
		}
/*
		if((munmap(PI, sharedSegSizePI)) != 0){
			printf("error unmap PI\n");
			exit(-1);
		}
*/
		if((munmap(resultadoFinal->PI, sharedSegSizePI)) != 0){
			printf("error unmap PI\n");
			exit(-1);
		}

		if((shm_unlink(SHARED_NAME_PI)) != 0){
			printf("error shm_unlink PI\n");
			exit(-1);
		}

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
	//TODO receber numero de Produtos Internos a calcular, ou seja, receber em qts linhas vai atuar, e achar um jeito de limitar(usar o k ou receber de algum modo).
	int numeroDePIsCalcular = 4;
	int* indices = (int*)calloc(sizeof(int), numeroDePIsCalcular);
	Resultado* resultado;
	int i;
	int j;

	for(j = 0, i = meuPidLogico * numeroDePIsCalcular; j < numeroDePIsCalcular; j++, i++){
		indices[j] = i;
	}

	//cast sem explicacao mas o compilador da warning. falando que tento fazer int em pointer sem cast
	resultado = (Resultado*)executaTarefa(indices, numeroDePIsCalcular);

	sem_wait(semaphore);

	resultadoFinal->mediaPI += resultado->mediaPI;
	resultadoFinal->mediaQuadradoPI += resultado->mediaQuadradoPI;
	resultadoFinal->maiorPI = (resultadoFinal->maiorPI > resultado->maiorPI) ? resultadoFinal->maiorPI : resultado->maiorPI;
	resultadoFinal->menorPI = (resultadoFinal->menorPI < resultado->menorPI) ? resultadoFinal->menorPI : resultado->menorPI;
	resultadoFinal->maiorElem = (resultadoFinal->maiorElem > resultado->maiorElem) ? resultadoFinal->maiorElem : resultado->maiorElem;
	resultadoFinal->menorElem = (resultadoFinal->menorElem < resultado->menorElem) ? resultadoFinal->menorElem : resultado->menorElem;

	/*printf("meuPidLogico=%d, maiorElem=%d, menorElem=%d, maiorPI=%d, menorPI=%d, mediaPI = %.4f, mediaQuadradoPI = %.4f\n", meuPidLogico, resultadoFinal->maiorElem, resultadoFinal->menorElem, resultadoFinal->maiorPI, resultadoFinal->menorPI, resultadoFinal->mediaPI, resultadoFinal->mediaQuadradoPI);*/

	sem_post(semaphore);

	free(resultado);	
}
