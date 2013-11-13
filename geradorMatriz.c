/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o tamanho informado durante a execução */

/* Instruções: Para rodar o programa corretamente, redirecione a saída padrão para o arquivo no qual você deseja salvar a matriz gerada.
   
   Exemplo:

   gcc geradorMatriz.c -o gerador
   ./gerador >> matriz.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int dim, i, j;

  scanf("%d", &dim);      //le da entrada o numero de quadrantes da matriz
  printf("%d\n", dim);    //imprime no arquivo de saida a dimensao da matriz, considerando o quadrante de tamanho 8x8

  //inicia o gerador de numeros aleatorios
  srand(time(NULL));

  //imprime a matriz de numeros aleatorios
  for(i=0; i<dim; i++){
    for(j=0; j<dim; j++){
      printf("%d ", (rand()%100)-50);  //gera numero inteiro entre -50 e 50
    }
    printf("\n");
  }

  return 0;
}
