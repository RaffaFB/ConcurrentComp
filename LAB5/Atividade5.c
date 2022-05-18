#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  5

int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

void* threadUm(void* arg){
  pthread_mutex_lock(&x_mutex);
  while(x < 4){
    pthread_cond_wait(&x_cond, &x_mutex);
  }
  pthread_mutex_unlock(&x_mutex);
  printf("''Volte sempre!''\n");

  pthread_exit(NULL);
}

void* threadDois(void* arg){
  pthread_mutex_lock(&x_mutex);
  if (x == 0) {
     pthread_cond_wait(&x_cond, &x_mutex);
  }
  pthread_mutex_unlock(&x_mutex);
  printf("''Fique a vontade.''\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  pthread_cond_broadcast(&x_cond);
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void* threadTres(void* arg){
  pthread_mutex_lock(&x_mutex);
  if (x == 0) {
     pthread_cond_wait(&x_cond, &x_mutex);
  }
  pthread_mutex_unlock(&x_mutex);
  printf("''Sente-se por favor''\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  pthread_cond_broadcast(&x_cond);
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void* threadQuatro(void* arg){
  pthread_mutex_lock(&x_mutex);
  if (x == 0) {
     pthread_cond_wait(&x_cond, &x_mutex);
  }
  pthread_mutex_unlock(&x_mutex);
  printf("''Aceita um copo d´água?''\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  pthread_cond_broadcast(&x_cond);
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void* threadCinco(void* arg){
  printf("''Seja bem-vindo!''\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  pthread_cond_broadcast(&x_cond);
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  int i;
  pthread_t threads[NTHREADS];

  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  pthread_create(&threads[4], NULL, threadCinco, NULL);
  pthread_create(&threads[0], NULL, threadUm, NULL);
  pthread_create(&threads[1], NULL, threadDois, NULL);
  pthread_create(&threads[2], NULL, threadTres, NULL);
  pthread_create(&threads[3], NULL, threadQuatro, NULL);

  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);

  return 0;
}
