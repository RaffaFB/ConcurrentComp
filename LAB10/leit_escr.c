#include <stdio.h>
#include <lpthread.h>
#include <semaphore.h>

sem_t em_e, em_l, escr, leit;
int e=0, l=0; 
int nthreadsL, nthreadsE;

void *leitores(void *args){
  int *id = (int*) args;
  while(1){
    sem_wait(&leit);
    sem_wait(em_l);
    l++;
    if(l==1) sem_wait(&escr);
    sem_post(&em_l);
    sem_post(&leit);
    printf("Leitor %d está lendo\n", id);
    sem_wait(&em_l);
    l--;
    if(l==0) sem_post(&escr);
    sem_post(&em_l);
  }
}

void *escritores(void *args){
  int *id = (int*) args;
  sem_wait(&em_e);
  e++;
  if(e==1) sem_wait(&leit);
  sem_post(&em_e);
  sem_wait(&escr);
  printf("escritor %d está escrevendo\n", id);
  sem_post(&escr);
  sem_wait(&em_e);
  e--;
  if(e==0) sem_post(%leit);
  sem_post(&em_e);
}

int main(int argc, char const *argv[]) {
  pthread_t tid[nthreadsE+nthreadsL];

  sem_init(&em_e, 0, 0);
  sem_init(&em_l, 0, 0);
  sem_init(&escr, 0, 0);
  sem_init(&leit, 0, 0);
  return 0;
}
