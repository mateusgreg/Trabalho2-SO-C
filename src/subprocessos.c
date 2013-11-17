
#include "subprocessos.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHARED_NAME "/shared"
#define SEM_NAME "/semaphore"
#define SEM_INIT_VALUE 1

Resultado* resultadoFinal;
sem_t* semaphore;

int getMinimumInt(){
	int nMin = 8;
	int nWidth = 8;
	while(0 < (nMin <<= 4)) nWidth += 4;
	return nMin;
}

int getMaximumInt(){
	return getMinimumInt()^-1;
}


Resultado* executaSubprocessos(int nsubprocessos){
	int i;
	int pid;
	int shmfd;
	int sharedSegSize = 1 * sizeof(Resultado);
	Resultado* resultado = (Resultado*) malloc(sizeof(Resultado));

	shmfd = shm_open(SHARED_NAME, O_CREAT | O_RDWR, 0666);
	if (shmfd == -1){
		printf("Erro shm_open aborting...\n");
		exit(-1);
	}

	if(ftruncate(shmfd, sharedSegSize) == -1){
		printf("error truncating\n");
		exit(-1);
	}

	resultadoFinal = mmap(NULL, sharedSegSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

	if(resultadoFinal == MAP_FAILED){
		printf("error mapping\n");
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

		if(sem_close(semaphore) != 0){
			printf("error sem_close\n");
			exit(-1);
		}

		if((munmap(resultadoFinal, sharedSegSize)) !=0){
			printf("error unmap\n");
			exit(-1);
		}

		if((shm_unlink(SHARED_NAME)) != 0){
			printf("error shm_unlink\n");
			exit(-1);
		}
	}

	return resultado;
}

void executaTarefaSubprocesso(int meuPidLogico){
	//TODO receber numero de Produtos Internos a calcular, ou seja, receber em qts linhas vai atuar, e achar um jeito de limitar(usar o k ou receber de algum modo).
	int numeroDePIsCalcular = 4;
	int* indices = (int*)calloc(sizeof(int), numeroDePIsCalcular);
	float mediaPI;
	float mediaQuadradoPI;
	int maiorElem;
	int menorElem;
	int maiorPI;
	int menorPI;
	int i;
	int j;

	for(j = 0, i = meuPidLogico * numeroDePIsCalcular; j < numeroDePIsCalcular; j++, i++){
		indices[j] = i;
	}

	executaTarefa(indices, numeroDePIsCalcular, &mediaPI, &mediaQuadradoPI, &maiorElem, &menorElem, &maiorPI, &menorPI);

	sem_wait(semaphore);

	resultadoFinal->mediaPI += mediaPI;
	resultadoFinal->mediaQuadradoPI += mediaQuadradoPI;
	resultadoFinal->maiorPI = (resultadoFinal->maiorPI > maiorPI) ? resultadoFinal->maiorPI : maiorPI;
	resultadoFinal->menorPI = (resultadoFinal->menorPI < menorPI) ? resultadoFinal->menorPI : menorPI;
	resultadoFinal->maiorElem = (resultadoFinal->maiorElem > maiorElem) ? resultadoFinal->maiorElem : maiorElem;
	resultadoFinal->menorElem = (resultadoFinal->menorElem < menorElem) ? resultadoFinal->menorElem : menorElem;

	printf("meuPidLogico=%d, maiorElem=%d, menorElem=%d, maiorPI=%d, menorPI=%d, mediaPI = %.4f, mediaQuadradoPI = %.4f\n", meuPidLogico, resultadoFinal->maiorElem, resultadoFinal->menorElem, resultadoFinal->maiorPI, resultadoFinal->menorPI, resultadoFinal->mediaPI, resultadoFinal->mediaQuadradoPI);

	sem_post(semaphore);

	
}
