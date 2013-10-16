/* Disciplina: Computação Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho: 1 */
/* Autores: Juan Baptista e Mateus Gregório */

/* Descrição: arquivo externo que contem as estruturas de dados e os protótipos das funções do módulo concorrente do programa */


/*Aloca espaco em memoria para um vetor de n inteiros */
int *alocaVetorInteiros(int n);

/*Aloca espaco em memoria para um vetor do tipo pthread_t de n elementos */
pthread_t *alocaVetorThreads(int n);

/*Aloca espaco em memoria para um vetor de semaforos de n elementos */
sem_t *alocaVetorSemaforos(int n);

/*Executa o processamento do quadrante correspondente ao id da thread. Calcula a soma, determina o maior e o menor de todos os elementos do quadrante */
void processaQuadrante(int tid);

/*Nucleo da solução do problema. Funcao executada por cada thread, executa o processamento da matriz de entrada:
  ira retornar a soma todos os elementos, o maior e o menor deles */
void *processaMatriz (void *threadid);

/*Funcao principal da solucao concorrente, que chama as demais funcoes e retorna o resultado final do processamento */
int *programaConcorrente(int **mat, int d);


//variaveis globais
int **matriz;  //matriz de entrada
int dim;  //dimensão da matriz
int *soma, *maior, *menor;  //vetores que armazenarão os resultados
int cont;  //variavel usada pra implementação da barreira
int nThreads;  //numero de threads
sem_t em, *continua;  //semaforos
