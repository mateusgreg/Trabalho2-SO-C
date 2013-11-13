/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o parâmetro informado em tempo de execução */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"

using namespace std;

//variáveis globais
int **matriz;  //ponteiro para a matriz a ser gerada
int k = 1;	   //dimensao da matriz de entrada

int main(int argc, char* argv[]) {

	int opcao;
	//variaveis utilizadas na contagem de tempo
	struct timeval startTime, endTime;
	unsigned int totalUsecs;

	while (k) {
		cout << "Digite a dimensão da matriz: ";
		scanf("%d", &k);

		matriz = geraMatriz(k);

		cout << "De que maneira você deseja fazer os cálculos da matriz gerada:" << endl;
		cout << "1. Sequencial" << endl;
		cout << "2. Subprocessos" << endl;
		cout << "3. Threads" << endl;

		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			//TODO:sequencial()
			break;
		case 2:
			//TODO:subprocessos()
			break;
		case 3:
			//TODO:threads();
			break;
		default:
			cout << "\nERRO: Argumento inválido!" << endl;
		}
	}


	return 0;
}
