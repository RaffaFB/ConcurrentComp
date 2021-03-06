#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

int s = 0;
pthread_mutex_t mutex;
long int dim, nthreads;
int * vetEntrada;
float * vetSaida;

void *tarefa(void* threadid){
  int i, id = (int*) threadid;
  long int tamBloco = dim/nthreads;
  long int ini = id * tamBloco;
  long int fim;
  float entrada, saida;

  if(id == nthreads-1) fim = dim;
  else fim = ini + tamBloco;

  //printf("rodando thread %d\n", id);
  for(i=ini; i<fim; i++){

    pthread_mutex_lock(&mutex);
    entrada = vetEntrada[i];
    pthread_mutex_unlock(&mutex);

    if ((ehPrimo(vetEntrada[i])) == 1){
      saida = sqrt(entrada);
    }else{
      saida = entrada;
    }

    pthread_mutex_lock(&mutex);
    vetSaida[i] = saida;
    pthread_mutex_unlock(&mutex);
    //printf("vetor concorrente %lf\n", vetSaida[i]);
  }
  pthread_exit(NULL);
}

int * preencheVetor(int dim){
  int * v;
  long int i;
  v = (int*) malloc(sizeof(int)*dim);
  if(v == NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }
  for(i=0; i<dim; i++){
     v[i] = rand() % 9;
     //printf("%d\n", v[i]);
  }
  return v;
}

int ehPrimo(int x){
  int i;
  if(x==2) return 1;
  for(i=2; i<=x/2; i++){
    if((x%i)==0){
      return -1;
    }
  }
  return 1;
}

void processaPrimos(int * vetorEntrada, float * vetorSaida, int dim) {
  for(int i=0; i<dim; i++) {
      if ((ehPrimo(vetorEntrada[i])) == 1){
        vetorSaida[i] = sqrt(vetEntrada[i]);
      }else{
        vetorSaida[i] = vetorEntrada[i];
      }
      //printf("Vetor sequencial: %lf\n", vetSaida[i]);
  }
}

int main(int argc, char const *argv[]) {
  pthread_t* tid;
  int *i;
  float ini, fim, tempoSeq, tempoConc;
  if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
      return 1;
  }
  dim = atoi(argv[1]);
  nthreads = atoi(argv[2]);
  vetEntrada = (int*) malloc(sizeof(int)*dim);
  vetSaida = (float*) malloc(sizeof(float)*dim);
  if(vetEntrada == NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }

  vetEntrada = preencheVetor(dim);

  GET_TIME(ini);
  processaPrimos(vetEntrada, vetSaida, dim);
  GET_TIME(fim);
  tempoSeq = fim - ini;
  printf("tempo sequencial: %lf\n", tempoSeq);



  GET_TIME(ini);
  tid = (pthread_t*) malloc(sizeof(int)*nthreads);
  if(tid==NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }

  pthread_mutex_init(&mutex, NULL);

  for(long int i=0; i<nthreads; i++) {
    if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
       fprintf(stderr, "ERRO--pthread_create\n");
       return 3;
    }
 }

 for(long int i=0; i<nthreads; i++) {
     if(pthread_join(*(tid+i), NULL)){
        fprintf(stderr, "ERRO--pthread_join\n");
        return 3;
     }
  }
  pthread_mutex_destroy(&mutex);
  
  GET_TIME(fim);
  tempoConc = fim-ini;
  printf("tempo concorrente: %lf\n", tempoConc);
  printf("ganho de desempenho %lf\n", tempoSeq/tempoConc);
  return 0;
}
