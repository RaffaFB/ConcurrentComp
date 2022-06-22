public class T2 extends Thread{
	int id;
	int delay;
	LeitorEscritor monitor;
	VariavelCompartilhada x;
	
	public T2(int id, LeitorEscritor monitor, VariavelCompartilhada x, int delay) {
		this.id = id;
		this.monitor = monitor;
		this.x = x;
		this.delay = delay;
	}
	
	public void run() {
		try {
			while(true) {
				this.monitor.EntraLeitor(this.id);
				if(this.x.getX()%2==0) {
					System.out.println("valor de x= "+this.x.getX()+" (par)");
				}else {
					System.out.println("valor de x= "+this.x.getX()+" (impar)");
				}
				this.monitor.SaiLeitor(this.id);
				sleep(this.delay);
			}	
		}catch(InterruptedException e) {
			return;
		}
		
	}
}
