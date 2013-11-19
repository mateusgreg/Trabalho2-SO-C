#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <stdlib.h>

#define x 1

int rc;
int i, j, k, id, d1, d2;

int main(void)
{
	printf("x = %d\n", x);
	d1 = 0; d2 = 0;
	j = 0;
	for (i = 0; i <= x; i++)
	{
		//***** mostre quem executa este trecho.
		printf("Processo: %d executa primeira linha dentro do primeiro for\n", getpid());
		//***** mostre o valor atual de d1 e d2.
		printf("segunda linha do primeiro for. d1 = %d e d2 = %d\n", d1, d2);
		rc = fork();
		if (rc)
		{
			//***** mostre quem executa este trecho.
			printf("Processo: %d executa primeira linha dentro do if(rc) dps do fork\n", getpid());
			d1 = d1 + (i + 1);
			d2 = d2 + d1 * 3;
			//***** mostre o valor e discuta o escopo de d1 e d2
			printf("Processo: %d dentro de if(rc) dps de calculado d1 e d2. d1 = %d e d2 = %d\n", getpid(), d1, d2);
		}else
		{
			//***** verifique quem executa este trecho.
			printf("Processo: %d executa primeira linha dentro do else do if(rc) dps do fork\n", getpid());
			j = i + 1;
			d1= d1 + 10;
			d2 = 1.5 * d1;
			//***** mostre o valor e o escopo de d1 e d2 e os compare com os valores no outro trecho.
			printf("Processo: %d dentro de else do if(rc) dps de calculado d1 e d2. d1 = %d e d2 = %d\n", getpid(), d1, d2);
		}

	}

	//***** diga quem executa este trecho.
	printf("Processo: %d executa primeira linha dps do primeiro for\n", getpid());
	if (rc != 0)
	{
		//***** verifique quem executa este trecho.
		printf("Processo: %d executa primeira linha dentro do if(rc != 0)\n", getpid());
		//for (i = j; i == x; i++)
		for (i = j; i <= x; i++)
		{
			//**** Verifique se o comando “for” está correto, de forma a aguardar todos os processos
			wait(&rc);
			if (rc == 0)
				//**** O que ocorre quando este trecho é executado?
				printf("Processo: %d observou um termino correto\n", getpid());
			else
				//**** O que ocorre quando este trecho é executado?
				printf("Processo: %d observou um termino incorreto\n", getpid());
		}
	}
	printf("Processo: %d FINALIZA\n", getpid());
	exit(0);
}
