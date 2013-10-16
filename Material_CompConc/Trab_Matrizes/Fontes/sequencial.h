/* Disciplina: Computação Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho: 1 */
/* Autores: Juan Baptista e Mateus Gregório */

/* Descrição: arquivo externo que contem os protótipos das funções do módulo sequencial do programa */


/*Aloca espaco em memoria para um vetore de n inteiros */
int *alocaVetorInteirosSeq(int n);

/*Nucleo da solução do problema. Executa o processamento da matriz de entrada:
  soma todos os elementos, verifica quem eh o maior e o menor deles */
int *processaMatrizSeq(int **mat, int dim);
