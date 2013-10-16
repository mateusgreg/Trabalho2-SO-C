/* Disciplina: Computação Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho: 1 */
/* Autores: Juan Baptista e Mateus Gregório */

/* Descrição: Módulo do programa responsável pela resolução do problema proposto de forma concorrente */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include "concorrente.h"


//aloca espaco em memoria para um vetor de n inteiros
int *alocaVetorInteiros(int n){
  int *vet;

  vet = calloc(n, sizeof(int));
  if (vet == NULL) {
       printf ("Erro de alocacao de memoria do vetor de inteiros.");
       return NULL;
  }

  return vet;  //retorna o ponteiro para o vetor
}


//aloca espaco em memoria para um vetor do tipo pthread_t de n elementos
pthread_t *alocaVetorThreads(int n){
  pthread_t *vet;

  vet = calloc(n, sizeof(pthread_t));
  if (vet == NULL) {
       printf ("Erro de alocacao de memoria do vetor de threads.");
       return NULL;
  }

  return vet;  //retorna o ponteiro para o vetor
}


//aloca espaco em memoria para um vetor de semaforos de n elementos
sem_t *alocaVetorSemaforos(int n){
  sem_t *vet;

  vet = calloc(n, sizeof(sem_t));
  if (vet == NULL) {
       printf ("Erro de alocacao de memoria do vetor de semaforos.");
       return NULL;
  }

  return vet;  //retorna o ponteiro para o vetor
}


//executa o processamento de um quadrante da matriz de entrada: soma os elementos e verifica quem eh o maior e o menor
void processaQuadrante(int tid){
  int i, j;
  int l, c;  //posicao do quadrante que a thread sera responsavel

  //calculo do quadrante que vai ser processado
  l = tid/(dim/8);
  c = tid%(dim/8);

  for(i=0; i<8; i++){
    for(j=0; j<8; j++){
        //calcula a soma dos elementos do quadrante
      if(soma[tid] == NULL) soma[tid] = matriz[i+l*8][j+c*8];
      else soma[tid] += matriz[i+l*8][j+c*8];

      //verifica quem eh o maior e o menor elemento do quadrante
      if( (maior[tid] == NULL) || (matriz[i+l*8][j+c*8] > maior[tid])) maior[tid] = matriz[i+l*8][j+c*8];
      else if( (menor[tid] == NULL) || (matriz[i+l*8][j+c*8] < menor[tid]) ) menor[tid] = matriz[i+l*8][j+c*8];
    }
  }
}


//funcao executada pelas threads, ira retornar a soma de todos os elementos, o maior e o menor deles
void *processaMatriz (void *threadid) {
  int tid = (int)threadid;
  int t;

  //thread executa o processamento do quadrante correspondente ao seu identificador (tid)
  processaQuadrante(tid);

  //variavel a ser utilizada na divisao do processamento dos vetores soma, maior e menor entre as threads
  int meio = nThreads;

  while(meio != 1){
    //verificacao da barreira: exclusao mutua para manipulacao da variavel cont
    sem_wait(&em);
    cont--;

    //verifica se todas as threads chegaram ate a barreira...
    if(cont==0){
      cont=meio/2;  //apenas metade das threads ira avancar a barreira
      //desbloqueia apenas a primeira metade das threads: threads cujo id pertence ao intervalo [0, (meio/2)-1]
      for(t=0; t<cont; t++){
        sem_post(&continua[t]);  //desbloqueia a thread cujo id eh t, permitindo que ela avance a barreira
      }
    }

    sem_post(&em);  //fim da exclusao mutua para acesso a variavel cont

    //caso a thread pertenca a segunda metade das threads ela encerra a sua execucao, já que nao sera mais utilizada
    if ((tid >= meio/2)){
      pthread_exit(NULL);
    }

    sem_wait(&continua[tid]);  //barreira: threads ficam bloqueadas neste ponto ate que a ultima thread emita o sinal de desbloqueio para as demais

    //processamento dos vetores soma, maior e menor apos a barreira
    if((meio%2 != 0) && tid == 0) {  //caso especial para numero impar de posicoes nos vetores soma, maior e menor
      soma[0] = soma[0] + soma[meio-1];
      if(maior[meio-1] > maior[0]) maior[0] = maior[meio-1];
      if(menor[meio-1] < menor[0]) menor[0] = menor[meio-1];
    }

    meio = meio/2;
    if(tid < meio) {  //demais casos em que o numero de posicoes nos vetores soma, maior e menor e par
      soma[tid] = soma[tid] + soma[tid+meio];
      if(maior[tid+meio] > maior[tid]) maior[tid] = maior[tid+meio];
      if(menor[tid+meio] < menor[tid]) menor[tid] = menor[tid+meio];
    }
  }
}


//Funcao principal da solucao concorrente, que chama as demais funcoes e retorna o resultado final do processamento
int *programaConcorrente(int **mat, int d){

  int *res;  //ponteiro para o vetor de resultados
  pthread_t *threads;  //ponteiro para o vetor de threads
  int t;

  //aloca memoria para o vetor que ira retornar o resultado final
  res = alocaVetorInteiros(3);

  matriz = mat;
  dim = d;

  nThreads = (dim/8) * (dim/8);  //calcula o numero de threads a serem criadas de acordo com o tamanho da matriz de entrada
  cont = nThreads;  //variavel contadora sera utilizada no controle da barreira

  //alocacao de memoria para os vetores de threads, semaforos e resultados
  threads = alocaVetorThreads(nThreads);
  continua = alocaVetorSemaforos(nThreads);
  soma = alocaVetorInteiros(nThreads);
  maior = alocaVetorInteiros(nThreads);
  menor = alocaVetorInteiros(nThreads);

  //incializa os semaforos
  sem_init(&em, 0, 1);
  for(t=0;t<nThreads;t++){
    sem_init(&continua[t], 0, 0);
  }

  //cria as threads
  for(t=0; t<nThreads; t++) {
    if (pthread_create(&threads[t], NULL, processaMatriz, (void *)t)) {
      printf("--ERRO: pthread_create()\n");
      exit(-1);
    }
  }

  //apenas espera o termino da thread 0, já que todas as outras ja terao sido encerradas
  if (pthread_join(threads[0], NULL)) {
    printf("--ERRO: pthread_join() \n");
    exit(-1);
  }

  //recuperando os resultados finais e armazenando no vetor a ser retornado
  res[0] = soma[0];
  res[1] = maior[0];
  res[2] = menor[0];

  //liberando a memoria
  free(soma);
  free(maior);
  free(menor);
  free(threads);
  free(continua);

  return res;
}
