#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long int dim; //dimensao do vetor de entrada
int nthreads; //numero de threads
double *vetor; //vetor de entrada com dimensao dim
float maior, menor;

void * tarefa(void * arg){
  long int id = (long int) arg;
  long int i,j,aux;
  double x[2];
  long int tamBloco = dim/nthreads;
  long int ini = id * tamBloco;
  long int fim;
  if(id == nthreads-1) fim = dim;
  else fim = ini + tamBloco;
  for(i = ini; i < fim; i++){
    for(j = ini; j < fim-i-1 ; j++){
      if(vetor[j] > vetor[j+1]){
        aux = vetor[j];
        vetor[j] = vetor[j+1];
        vetor[j+1] = aux;
      }
    }
  }
  x[0] = vetor[0];
  x[1] = vetor[fim];
  pthread_exit((void *) x);
}


double * preencheVetor(int dim){
  double * v;
  long int i;
  v = (double*) malloc(sizeof(double)*dim);
  if(v == NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }
  for(i=0; i<dim; i++){
     v[i] = ((float)rand()/(float)(RAND_MAX)) * 10.0;
     printf("%lf\n", v[i]);
  }
  return v;
}

void * maior_menor(double *v, int dim){
  int i, j, aux;
  for(i = 0; i < dim; i++){
    for(j = 0; j < dim-i-1 ; j++){
      if(v[j] > v[j+1]){
        aux = v[j];
        v[j] = v[j+1];
        v[j+1] = aux;
      }
    }
  }
  maior = v[dim-1];
  menor = v[0];
}


int main(int argc, char const *argv[]) {
  double ini, fim; 
  pthread_t *tid;
  double *retorno;

  if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
      return 1;
  }
  dim = atoi(argv[1]);
  nthreads = atoi(argv[2]);
  vetor = (double*) malloc(sizeof(double)*dim);
  if(vetor == NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }

  vetor = preencheVetor(dim);

  GET_TIME(ini);
  maior_menor(vetor, dim);
  printf("maior: %lf, menor: %lf\n", maior, menor);
  GET_TIME(fim);
  printf("Tempo sequencial:  %lf\n", fim-ini);

  tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid==NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }

  for(long int i=0; i<nthreads; i++) {
     if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
        fprintf(stderr, "ERRO--pthread_create\n");
        return 3;
     }
  }

  for(long int i=0; i<nthreads; i++) {
     if(pthread_join(*(tid+i), (void**) &retorno)){
        fprintf(stderr, "ERRO--pthread_create\n");
        return 3;
     }
     printf("%lf\n", x[0]);
  }

  return 0;
}
