class Task extends Thread{
  private int id;
  int size;
  int vector[];
  public Task(int vector[], int size){
    this.size = size;
    for(int c=0; c<size; c++){
      this.vector[i] = vector[i];
    }
  };
  public static int isEven;

  public void run(int vector[]){
    int blockSize = size/nthreads;
    int init = id * blockSize;
    int end;
    if(id == nthreads-1){
      end = size;
    }else{
      end = init + blockSize;
    }
    for(int j=init; j<end; j++){
      for(int z=init; z=end-j-1; z++){
        if(vetor[z]%2 == 0) isEven++;
      }
    }
  }
}
class EvenNumbers{
  static final int nthreads = 2;
  public static void main(String[] args) {
    int size = 10;
    int i;
    int vector[] = new int[size];
    for(i=0; i<size; i++){
      vector[i] = i;
    }

    Thread[] threads = new Thread[N];
    for(i=0; i<threads.length; i++){
      System.out.println("Rodando thread: " + i);
      threads[i] = new Task(vector[], size);
    }

    for (int i=0; i<threads.length; i++) {
       threads[i].start();
    }

    for (int i=0; i<threads.length; i++) {
       try { threads[i].join(); }
       catch (InterruptedException e) { return; }
    }

  }
}
