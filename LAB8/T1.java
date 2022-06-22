public class T1 extends Thread{
	int id;
	int delay;
	VariavelCompartilhada x;
	LeitorEscritor monitor;
	
	public T1(int id, VariavelCompartilhada x, LeitorEscritor monitor, int delay) {
		this.id = id;
		this.x = x;
		this.monitor = monitor;
		this.delay = delay;
	}
	
	public void run() {
		try {
			while(true) {
				this.monitor.EntraEscritor(this.id);
				this.x.inc();
				this.monitor.SaiEscritor(this.id);
				sleep(this.delay);
			}
		}catch(InterruptedException e) {
			return;
		}
		
	}
}
