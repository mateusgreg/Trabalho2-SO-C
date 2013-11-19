/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: API Pública utilizada pelos 3 módulos do programa, auxilia na divisão e execução das tarefas entre as unidades de execução. */


#include "resultado.h"

typedef struct _tarefas {
	int inicio;
	int fim;
}Tarefas;

Tarefas* divideTarefas(int undExecucao);

/*
recebe i, a linha e coluna em cima de onde calcular o PI e referencias para o maior e menor elemento
retorna o valor do PI e, por referencia os valores do maior e menor elemento
*/
unsigned long long int produtoInternoEMaiorMenorElementoParcial(int i, int* maiorElem, int* menorElem);

/*
recebe vetor contendo os indices das linhas/colunas das quais
ira calcular os PIs
retorna ponteiro para Resultado que contem mediaPI, media Parcial dos PIs, mediaQuadradoPI,
media parcial dos quadrados dos PIs usado no calculo do desvio padrao,
meiorElem, maior elemento parcial da matriz gerada,
menorElem, menor elemento parcial da matriz gerada,
maiorPI, maior PI parcial,
menorPI, menor PI parcial
*/
Resultado* executaTarefa(Tarefas* tarefas);
