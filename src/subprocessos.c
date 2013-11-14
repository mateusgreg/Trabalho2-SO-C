
#include "subprocessos.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void executaSubprocessos(int nsubprocessos, float mediasPI[], float mediasQuadradoPI[], int maioresPI[], int menoresPI[], int maioresElem[], int menoresElem[]){
	int i;
	int pid;
	for(i = 0; i < nsubprocessos; i++){
		pid = fork();
		if(pid < 0){ printf("Erro ao criar subprocessos, abortando...\n"); exit(-1); }
		if(pid == 0){
			executaTarefaSubprocesso(i, mediasPI, mediasQuadradoPI, maioresPI, menoresPI, maioresElem, menoresElem);
			exit(0);
		}
	}

	if(pid > 0){
		for(i = 0; i < nsubprocessos; i++){
			wait(NULL);
		}
	}

	
}

void executaTarefaSubprocesso(int meuPidLogico, float mediasPI[], float mediasQuadradoPI[], int maioresPI[], int menoresPI[], int maioresElem[], int menoresElem[]){
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

	
	mediasPI[meuPidLogico] = mediaPI;
	mediasQuadradoPI[meuPidLogico] = mediaQuadradoPI;
	maioresPI[meuPidLogico] = maiorPI;
	menoresPI[meuPidLogico] = menorPI;
	maioresElem[meuPidLogico] = maiorElem;
	menoresElem[meuPidLogico] = menorElem;

	printf("maiorElem=%d, menorElem=%d, maiorPI=%d, menorPI=%d, mediaPI = %.4f, mediaQuadradoPI = %.4f\n", maioresElem[meuPidLogico], menoresElem[meuPidLogico], maioresPI[meuPidLogico], menoresPI[meuPidLogico], mediasPI[meuPidLogico], mediasQuadradoPI[meuPidLogico]);
	
}
