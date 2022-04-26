#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h>

int *mat1, *mat2;
int *saidaSeq, *saidaConc;
int nthreads;

typedef struct{
   int id;
   int dim;
} tArgs;

void * multiplica(void *arg) {
   tArgs *args = (tArgs*) arg;
   int i,j,k;
   for(i = args->id; i<args->dim; i++){
     for(j = args->id; j<args->dim; j++){
       for(k = 0; k<args->dim; k++){
         saidaConc[i*(args->dim)+j] += mat1[i*(args->dim)+k] * mat2[k*(args->dim)+j];
       }
       printf("%d\n", saidaConc[i*(args->dim)+j]);
     }
   }


   pthread_exit(NULL);
}

//thread principal
int main(int argc, char* argv[]) {
   int dim;
   pthread_t *tid;
   tArgs *args;
   double inicio, fim, delta;

   printf("Digite: a dimensao da matriz");
   scanf("%d", &dim);

   nthreads = dim;

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
   //multiplicacao sequencial:
   for(int i = 0; i<dim; i++){
     for(int j = 0; j<dim; j++){
       for(int k = 0; k<dim; k++){
         saidaSeq[i*dim+j] += mat1[i*dim+k] * mat2[k*dim+j];
       }
     }
   }

   tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
   if(tid==NULL) {puts("ERRO--malloc"); return 2;}
   args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
   if(args==NULL) {puts("ERRO--malloc"); return 2;}


   for(int i=0; i<nthreads; i++) {
      (args+i)->id = i;
      (args+i)->dim = dim;
      printf("criando thread:\n");
      if(pthread_create(tid+i, NULL, multiplica, (void*) (args+i))){
         puts("ERRO--pthread_create"); return 3;
      }
   }

   for(int i=0; i<nthreads; i++) {
      pthread_join(*(tid+i), NULL);
   }

   free(mat1);
   free(mat2);
   free(saidaSeq);
   free(saidaConc);
   free(args);
   free(tid);
   return 0;
 }
