/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Estrutura de Dados definida para concentrar todos os resultados oriundos do processamento da matriz. Foi criada para facilitar a manipulação dos dados e organizar melhor o código. */


#ifndef RESULTADO_H
#define RESULTADO_H

typedef struct _resultado{
	int maiorElem;
  	int menorElem;
	unsigned long long int* PI;
  	unsigned long long int maiorPI;
  	unsigned long long int menorPI;
  	double mediaPI;
  	double mediaQuadradoPI;
  	double tempoEmMilis;
	double tempoEmMicros;
} Resultado;

#endif //RESULTADO_H
