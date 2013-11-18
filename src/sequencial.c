/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Módulo Sequencial. Aqui não há divisão de tarefas, a própria thread main é quem realiza todo o processamento da matriz. */


#include <stdio.h>
#include <stdlib.h>
#include "tarefa.h"


//variaveis globais
Resultado* resultadoFinal;


Resultado* sequencial(int k, int* PI) {
  
  /*
	Tarefas *tarefas = (Tarefas*)malloc(sizeof(Tarefas));
	tarefas.inicio = 0;
	tarefas.fim = k-1;

	return executaTarefa(tarefas);
  */

	int i;
	int* indices = malloc(k * sizeof(int));

	for (i=0; i<k; i++) {
		indices[i] = i;
	}

	resultadoFinal = (Resultado*)malloc(sizeof(Resultado));
	resultadoFinal->PI = (int*)malloc(k * sizeof(int));

	Resultado* resultadoParcial = executaTarefa(indices, k);

	resultadoFinal->mediaPI = resultadoParcial->mediaPI;
	resultadoFinal->mediaQuadradoPI = resultadoParcial->mediaQuadradoPI;
	resultadoFinal->maiorPI = resultadoParcial->maiorPI;
	resultadoFinal->menorPI = resultadoParcial->menorPI;
	resultadoFinal->maiorElem = resultadoParcial->maiorElem;
	resultadoFinal->menorElem = resultadoParcial->menorElem;

	return resultadoFinal;
}
