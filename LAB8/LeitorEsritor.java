public class LeitorEscritor {
	private int leitor, escritor;
	
	LeitorEscritor(){
		this.leitor = 0;
		this.escritor = 0;
	}
	
	public synchronized void EntraLeitor(int id) {
		try {
			while(this.escritor > 0) {
				System.out.println("leitor "+id+" bloqueado");
				wait();
			}
			this.leitor++;
			System.out.println("leitor "+id+" lendo");
		}catch(InterruptedException e) {}
	}
	
	public synchronized void SaiLeitor(int id) {
		this.leitor--;
		if(this.leitor == 0) {
			this.notify();
		}
		System.out.println("leitor "+id+" saindo");
	}
	
	
	public synchronized void EntraEscritor(int id) {
		try {
			while((this.leitor > 0) || (this.escritor > 0)) {
				System.out.println("escritor "+id+" bloqueado");
				wait();
			}
			this.escritor++;
			System.out.println("escritor "+id+" escrevendo");
		}catch (InterruptedException e) { }
	}
	
	public synchronized void SaiEscritor(int id) {
	     this.escritor--; 
	     notifyAll(); 
	     System.out.println ("escritor "+id+" saindo");
	  }
}
