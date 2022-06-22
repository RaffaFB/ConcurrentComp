public class T3 extends Thread{
	int id;
	int j;
	int delay;
	LeitorEscritor monitor;
	VariavelCompartilhada x;
	
	public T3(int id, LeitorEscritor monitor, VariavelCompartilhada x, int delay) {
		this.id = id;
		this.monitor = monitor;
		this.x = x;
		this.delay = delay;
	}
	
	public void run() {
		try {
			while(true) {
				this.monitor.EntraLeitor(this.id);
				System.out.println("valor de x = "+this.x.getX());
				this.monitor.SaiLeitor(this.id);
				sleep(this.delay);
				
				for (int i=0; i<1000000000; i++) {
					j=j/2;
				}
				
				this.monitor.EntraEscritor(this.id);
				this.x.setX(this.id);
				this.monitor.SaiEscritor(this.id);
				sleep(this.delay);
			}	
		}catch(InterruptedException e) {
			return;
		}
		
	}
}
