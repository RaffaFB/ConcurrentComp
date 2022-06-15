public class EvenNumbers {
	public static void main(String[] args) {
		int nthreads = 4;
		int size = 10;
		int[] vector = new int[size];
		isEven even = new isEven();
		
		for(int i=0; i<size; i++) {
			vector[i] = i;
		}
		
		Thread[] threads = new Thread[nthreads];
	    for(int i=0; i<threads.length; i++){
	      System.out.println("Rodando thread: " + i);
	      threads[i] = new Task(nthreads, i, even, vector, size);
	    }

	    for (int i=0; i<threads.length; i++) {
	       threads[i].start();
	    }

	    for (int i=0; i<threads.length; i++) {
	       try { threads[i].join(); }
	       catch (InterruptedException e) { return; }
	    }
	    System.out.println("Quantidade de pares = " + even.getEven());

	}

}
