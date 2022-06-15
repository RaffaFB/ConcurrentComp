#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long int dim;
int nthreads;
double *vetor;
double maior, menor;
double *maiorConc, *menorConc;

void * tarefa(void * arg){
  long int id = (long int) arg;
  long int i,j,aux;
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
  menorConc[id] = vetor[ini];
  maiorConc[id] = vetor[fim-1];

  pthread_exit(NULL);
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
     v[i] = ((float)rand()/(float)(RAND_MAX)) * 9.0;
  }
  return v;
}

void * maior_menor(double *v, int dim){
  int i, j;
  double aux;
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
  double ini, fim, tempoSeq, tempoConc;
  pthread_t *tid;
  double x, y;

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
  printf("maior: %lf, menor: %lf (sequencial)\n", maior, menor);
  GET_TIME(fim);
  tempoSeq = fim-ini;
  printf("Tempo sequencial:  %lf\n", tempoSeq);

  maiorConc = (double*) malloc(sizeof(double)*nthreads);
  if(maiorConc==NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }
  menorConc = (double*) malloc(sizeof(double)*nthreads);
  if(menorConc==NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }

  GET_TIME(ini);
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
     if(pthread_join(*(tid+i), NULL)){
        fprintf(stderr, "ERRO--pthread_join\n");
        return 3;
     }
  }
  maior_menor(maiorConc, nthreads);
  x = maior;
  maior_menor(menorConc, nthreads);
  y = menor;
  printf("maior: %lf, menor: %lf (concorrente)\n", x, y);
  GET_TIME(fim);
  tempoConc = fim-ini;
  printf("Tempo concorrente:  %lf\n", tempoConc);
  printf("Ganho de desempenho: %lf\n", tempoSeq/tempoConc);


  return 0;
}
