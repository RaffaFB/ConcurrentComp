#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  2
#define SIZE 10000

typedef struct{
  int *vector, initV, finalV;
}t_Args;


void *powVector(void *arg){
  t_Args *args = (t_Args *) arg;
  int y, temp;
  for(y = args->initV; y < args->finalV; y++){
    temp = args->vector[y];
    args->vector[y] = args->vector[y]*args->vector[y];
    printf("%d^2 == %d\n", temp, args->vector[y]);
  }
  free(arg);
  pthread_exit(NULL);
}

int *vet(){
  int j, *v;
  v = calloc(SIZE, sizeof(int));
  if(v == NULL){
    printf("--ERRO: calloc\n"); exit(-1);
    return 0;
  }
  for(j=0; j<SIZE; j++){
    v[j] = j;
  }
  return v;
}

int main(){
  pthread_t tid_sistema[NTHREADS];
  int i, *vector;
  t_Args *tArgs;

  vector = vet();

  for(i=1; i<=NTHREADS; i++){
    tArgs = malloc(sizeof(t_Args));
    if(tArgs == NULL){
      printf("--ERRO: malloc\n"); exit(-1);
      return 0;
    }
    tArgs->vector = vector;

    if(i==1){
      tArgs->initV = 0;
      tArgs->finalV = SIZE/2;
    }else{
      tArgs->initV = SIZE/2;
      tArgs->finalV = SIZE;
    }
    printf("criando a thread %d\n", i);
    if (pthread_create(&tid_sistema[i], NULL, powVector, (void*) tArgs)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  for(i=1; i<=NTHREADS; i++){
    if (pthread_join(tid_sistema[i], NULL)) {
       printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }
      printf("fim da thread principal\n");
      pthread_exit(NULL);
}
