#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 5

sem_t sem1, sem2, sem3, sem4;

void* t1(void* arg){
  int* tid = (int*) arg;
  sem_wait(&sem2);
  sem_wait(&sem3);
  sem_wait(&sem4);
  printf("Volte sempre!\n");
  pthread_exit(NULL);
}

void* t2(void* arg){
  int* tid = (int*) arg;
  sem_wait(&sem1);
  printf("Fique a vontade\n");
  sem_post(&sem1);
  sem_post(&sem2);
  pthread_exit(NULL);
}

void* t3(void* arg){
  int* tid = (int*) arg;
  sem_wait(&sem1);
  printf("Sente-se por favor\n");
  sem_post(&sem1);
  sem_post(&sem3);
  pthread_exit(NULL);
}

void* t4(void* arg){
  int* tid = (int*) arg;
  sem_wait(&sem1);
  printf("Aceita um copo d'água?\n");
  sem_post(&sem1);
  sem_post(&sem4);
  pthread_exit(NULL);
}

void* t5(void* arg){
  int* tid = (int*) arg;
  printf("Seja bem-vindo!\n");
  sem_post(&sem1);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t tid[NTHREADS];
  int* id[5];

  for (int t=0; t<NTHREADS; t++) {
    if ((id[t] = malloc(sizeof(int))) == NULL) {
       pthread_exit(NULL); return 1;
    }
    *id[t] = t+1;
  }

  sem_init(&sem1, 0, 0);
  sem_init(&sem2, 0, 0);
  sem_init(&sem3, 0, 0);
  sem_init(&sem4, 0, 0);

  if (pthread_create(&tid[4], NULL, t5, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[3], NULL, t4, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[2], NULL, t3, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[1], NULL, t2, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[0], NULL, t1, NULL)) { printf("--ERRO: pthread_create()\n"); exit(-1); }

  for (int t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }
    free(id[t]);
  }

  sem_destroy(&sem1);
  sem_destroy(&sem2);
  sem_destroy(&sem3);
  sem_destroy(&sem4);
  pthread_exit(NULL);
}
