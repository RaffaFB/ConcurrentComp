public class isEven {
	private static int count;
	public isEven() {
		isEven.count = 0;
	}
	
	public synchronized void inc() {
		isEven.count++;
	}
	
	public synchronized int getEven() { 
	      return isEven.count; 
	  }
}
