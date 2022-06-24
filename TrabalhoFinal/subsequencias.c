#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long int nthreads, dim, dimSubsequencia;
char *vetor;
char* vetorSubsequencia;
int sub;
pthread_mutex_t mutex;

void *tarefa(void *arg){
  long int id = (long int) arg;
  long int tamBloco = dim/nthreads;
  long int inicio = id * tamBloco;
  long int fim;
  int aux = 0;
  if(id == nthreads-1) fim = dim;
  else fim = inicio + tamBloco;

  for(int i=inicio; i<fim; i++){
    int ehSub = 0;
    if(vetor[i] == vetorSubsequencia[0]){
      aux += ehSubsequencia(i);
    }
  }
  pthread_mutex_lock(&mutex);
  sub += aux;  // variavel global para contagem concorrente de subsequencias
  pthread_mutex_unlock(&mutex);
}

char *preencheVetor(){
  char *vetorAux;
  int i;
  vetorAux = (char*) malloc(sizeof(char)*dim);
  if(vetorAux==NULL){
    fprintf(stderr, "ERRO--malloc\n");
    return 2;
  }
  for(i=0; i<dim; i++){
    vetorAux[i] = 'A' + (random() % 26); //preenche vetor aleatoriamente de A a Z
    //printf("%c\n", vetorAux[i]);
  }
  return vetorAux;
}

int ehSubsequencia(int posicao){ // compara subsequencia com a parte do vetor de i a dimSubsequencia-1
  int ehSub = 0;
  int qntSub=0;

  ehSub++;
  for(int j=1; j<dimSubsequencia; j++){
    if(vetor[posicao+j] == vetorSubsequencia[j]) {ehSub++;}
  }
  if(ehSub == dimSubsequencia){
    qntSub++;
  }
  return qntSub;
}

void qntSubsequencias(){ // calcula quantas vezes uma subsequencia aparece no vetor
  int aux = 0;
  for(int i=0; i<dim; i++){
    if(vetor[i] == vetorSubsequencia[0]){
      aux += ehSubsequencia(i);
    }
  }
  printf("quantidade de subsequencias (versao sequencial): %d\n", aux);
}


int main(int argc, char const *argv[]) {
  pthread_t *tid;
  float ini, fim, tempoSeq, tempoConc;

  if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads> <tamanho da subsequencia>\n", argv[0]);
      return 1;
  }
  dim = atoi(argv[1]);
  nthreads = atoi(argv[2]);
  dimSubsequencia = atoi(argv[3]);

  vetorSubsequencia = (char*) malloc(sizeof(char)*dimSubsequencia);
  vetor = (char*) malloc(sizeof(char)*dim);
  if(vetor == NULL || vetorSubsequencia == NULL) {
     fprintf(stderr, "ERRO--malloc\n");
     return 2;
  }
  vetor = preencheVetor(dim);

  printf("Digite a subsequencia a ser procurada (de A a Z):\n");
  scanf("%s", vetorSubsequencia);

  GET_TIME(ini);
  qntSubsequencias(); //versao sequencial
  GET_TIME(fim);
  tempoSeq = fim - ini;
  printf("tempo sequencial: %lf\n", tempoSeq);

  GET_TIME(ini);
  tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
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
  printf("quantidade de subsequencias(versao concorrente): %d\n", sub);
  GET_TIME(fim);
  tempoConc = fim-ini;
  printf("tempo concorrente: %lf\n", tempoConc);
  printf("ganho de desempenho %lf\n", tempoSeq/tempoConc);
  return 0;
}
