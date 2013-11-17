/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o parâmetro informado em tempo de execução */


#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "resultado.h"
#include "sequencial.h"
#include "subprocessos.h"
#include "threads.h"

//variáveis globais
int k = 1;
int** matrizGerada;
int* PI;

int main(int argc, char* argv[]) {

	int opcao, invalido, undExecucao;
	Resultado* resultado;

	while (k) {
		printf("Digite a dimensão da matriz: ");
		scanf("%d", &k);

		matrizGerada = geraMatriz(k);

		do {
			printf("De que maneira você deseja fazer os cálculos da matriz gerada:\n");
			printf("1. Sequencial\n")
			printf("2. Subprocessos\n");
			printf("3. Threads\n");

			printf("\nOpção: ");
			scanf("%d", &opcao);

			switch(opcao) {
			case 1:
				//TODO:sequencial();
				break;
			case 2:
				//TODO:subprocessos();
				break;
			case 3:
				//TODO:threads();
				break;
			default:
				printf("\nERRO: Menu inválido!\n");
				invalido = 1;
			}
		}while (invalido);
		

		//TODO:Imprimir as respostas na console para o usuário.
	}


	return 0;
}
