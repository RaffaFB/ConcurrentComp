#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

int *mat1, *mat2;
int *saidaSeq, *saidaConc;
int nthreads, dim;


typedef struct{
   int id;
   int dim;
} tArgs;

void * multiplica(void *arg) {
  tArgs *args = (tArgs*) arg;
  int i,j,k;
  for(i = args->id; i<args->dim; i+=nthreads){
    for(j = 0; j<args->dim; j++){
      for(k = 0; k<args->dim; k++){
        saidaConc[i*(args->dim)+j] += mat1[i*(args->dim)+k] * mat2[k*(args->dim)+j];
      }
    }
  }
  pthread_exit(NULL);
}

//multiplicaçao Sequencial
void * multiplicaSequencial(int dim){

  for(int i = 0; i<dim; i++){
    for(int j = 0; j<dim; j++){
      for(int k = 0; k<dim; k++){
        saidaSeq[i*dim+j] += mat1[i*dim+k] * mat2[k*dim+j];
      }
    }
  }

  return saidaSeq;
}

//checa se os resultados são os mesmos
void comparaMatrizes(int* saidaSeq, int* saidaConc){
  for(int i = 0; i<dim; i++){
    for(int j = 0; j<dim; j++){
      if(saidaSeq[i*dim+j] =! saidaConc[i*dim+j]){
        puts("ERRO--matrizes diferentes");
        exit(-1);
      }
    }
  }
}

//thread principal
int main(int argc, char* argv[]) {
   int dim;
   pthread_t *tid;
   tArgs *args;
   double inicio, fim, aceleracao, delta1, delta2;

   if(argc<3) {
      printf("Digite: %s dimensao da matriz | numero de threads\n", argv[0]);
      return 1;
   }
   dim = atoi(argv[1]);
   nthreads = atoi(argv[2]);

   mat1 = (int *) malloc(sizeof(int) * dim * dim);
   if (mat1 == NULL) {printf("ERRO--malloc\n"); return 2;}
   mat2 = (int *) malloc(sizeof(int) * dim * dim);
   if (mat2 == NULL) {printf("ERRO--malloc\n"); return 2;}
   saidaSeq = (int *) malloc(sizeof(int) * dim * dim);
   if (saidaSeq == NULL) {printf("ERRO--malloc\n"); return 2;}
   saidaConc = (int *) malloc(sizeof(int) * dim * dim);
   if (saidaConc == NULL) {printf("ERRO--malloc\n"); return 2;}

   for(int i=0; i<dim; i++) {
      for(int j=0; j<dim; j++){
         mat1[i*dim+j] = rand() % 10;
         mat2[i*dim+j] = rand() % 10;
         saidaSeq[i*dim+j] = 0;
         saidaConc[i*dim+j] = 0;
      }
   }

   GET_TIME(inicio);

   multiplicaSequencial(dim);
   
   GET_TIME(fim);
   delta1 = fim - inicio;
   printf("Tempo multiplicacao sequencial (dimensao %d) (nthreads %d): %lf\n", dim, nthreads, delta1);

   tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
   if(tid==NULL) {puts("ERRO--malloc"); return 2;}
   args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
   if(args==NULL) {puts("ERRO--malloc"); return 2;}

   //criando a thread
   GET_TIME(inicio);
   for(int i=0; i<nthreads; i++) {
      (args+i)->id = i;
      (args+i)->dim = dim;
      if(pthread_create(tid+i, NULL, multiplica, (void*) (args+i))){
         puts("ERRO--pthread_create"); return 3;
      }
   }

   for(int i=0; i<nthreads; i++) {
      pthread_join(*(tid+i), NULL);
   }
   GET_TIME(fim);
   delta2 = fim - inicio;
   printf("Tempo multiplicacao concorrente (dimensao %d) (nthreads %d): %lf\n", dim, nthreads, delta2);


   comparaMatrizes(saidaSeq, saidaConc);

   aceleracao = delta1/delta2;
   printf("ganho de desempenho: %lf / %lf = %lf\n", delta1, delta2, aceleracao);

   free(mat1);
   free(mat2);
   free(saidaSeq);
   free(saidaConc);
   free(args);
   free(tid);
   return 0;
 }

