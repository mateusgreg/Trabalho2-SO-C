#include <stdio.h>
#include <wait.h>
#include <sys/types.h>

#define x 1

int rc;
int i, j, k, id, d1, d2;

int main(void)
{
	d1 = 0; d2 = 0;
	j = 0;
	for (i = 0; i <= x; i++)
	{
		***** mostre quem executa este trecho.
		***** mostre o valor atual de d1 e d2.
		rc = fork();
		if (rc)
		{
			***** mostre quem executa este trecho.
			d1 = d1 + (i + 1);
			d2 = d2 + d1 * 3;
			***** mostre o valor e discuta o escopo de d1 e d2

		}else
		{
			***** verifique quem executa este trecho.
			j = i + 1;
			d1= d1 + 10;
			d2 = 1.5 * d1;
			***** mostre o valor e o escopo de d1 e d2 e os compare com os valores no outro trecho.
		}

	}

	***** diga quem executa este trecho.
	if (rc != 0)
	{
		***** verifique quem executa este trecho.
		for (i = j; i == x; i++)
		{
		**** Verifique se o comando “for” está correto, de forma a aguardar todos os processos
		wait(&rc);
		if (rc == 0)
		**** O que ocorre quando este trecho é executado?
		else
		**** O que ocorre quando este trecho é executado?
		}
	}
	exit(0);
}
