public class Task extends Thread{
	private int id;
	public isEven even;
	int[] vector;
	int size;
	int nthreads;
	
	public Task(int nthreads, int tid, isEven even, int[] vector, int size) {
		this.nthreads = nthreads;
		this.even = even;
		this.id = tid;
		this.size = size;
		this.vector = new int[size];
		
		for(int i=0; i<size; i++) {
			this.vector[i] = vector[i];
		}
	}
	
	public void run() {
		int blockSize = size/nthreads;
	    int init = id * blockSize;
	    int end;
	    
	    if(id == nthreads-1){
	      end = size;
	    }else{
	      end = init + blockSize;
	    }
	    for(int x=init; x<end; x++) {
	    	if(vector[x]%2 == 0)
	        	this.even.inc();
	    }
	}
}
