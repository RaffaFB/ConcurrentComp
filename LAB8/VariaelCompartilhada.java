public class VariavelCompartilhada {
	private static int x;
	
	public VariavelCompartilhada() {
		VariavelCompartilhada.x = 0;
	}
	
	public synchronized void inc() {
		VariavelCompartilhada.x++;
	}
	
	public synchronized void dec() {
		VariavelCompartilhada.x--;
	}
	
	public synchronized void setX(int y) {
		VariavelCompartilhada.x = y;
	}
	
	public synchronized int getX() { 
	    return VariavelCompartilhada.x; 
	}
}
