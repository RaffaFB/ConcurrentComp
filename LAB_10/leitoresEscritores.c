#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t em_e, em_l, escr, leit;
int e=0, l=0;
int nthreadsL = 4, nthreadsE = 2;

void *leitores(void *args){
  int id = *(int*) args;
  while(1){
    printf("leitor %d quer ler\n", id);
    sem_wait(&leit);
    sem_wait(&em_l);
    l++;
    if(l==1){
      sem_wait(&escr);
    }
    sem_post(&em_l);
    sem_post(&leit);
    printf("--leitor %d está lendo\n", id);
    sem_wait(&em_l);
    l--;
    if(l==0){
      sem_post(&escr);
    }
    sem_post(&em_l);
  }
}

void *escritores(void *args){
  int id = *(int*) args;
  while(1){
    printf("escritor %d quer escrever\n", id);
    sem_wait(&em_e);
    e++;
    if(e==1){
      sem_wait(&leit);
    }
    sem_post(&em_e);
    sem_wait(&escr);
    printf("--escritor %d está escrevendo\n", id);
    sem_post(&escr);
    sem_wait(&em_e);
    e--;
    if(e==0){
      sem_post(&leit);
    }
    sem_post(&em_e);
  }
}

int main(int argc, char const *argv[]) {
  pthread_t tid[nthreadsE+nthreadsL];
  int t, id[nthreadsE+nthreadsL];

  sem_init(&em_e, 0, 1);
  sem_init(&em_l, 0, 1);
  sem_init(&escr, 0, 1);
  sem_init(&leit, 0, 1);

  for (t=0; t<nthreadsE; t++) {
     id[t]=t;
     if (pthread_create(&tid[t], NULL, escritores, (void *)&id[t])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  }
  for (t=nthreadsL; t<nthreadsE+nthreadsL; t++) {
     id[t]=t-nthreadsL;
     if (pthread_create(&tid[t], NULL, leitores, (void *)&id[t])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  }

  for (t=0; t<nthreadsE+nthreadsL; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }
  pthread_exit(NULL);

  return 0;
}
