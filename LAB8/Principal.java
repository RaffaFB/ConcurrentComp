public class Principal {
	public static int t1 = 2;
	public static int t2 = 2;
	public static int t3 = 2;
	
	public static void main(String[] args) {
		int i;
		LeitorEscritor monitor = new LeitorEscritor();
		VariavelCompartilhada x = new VariavelCompartilhada();
		
		T1[] v1 = new T1[t1];
		T2[] v2 = new T2[t2];
		T3[] v3 = new T3[t3];
		
		System.out.println ("import verificaLE");
	    System.out.println ("le = verificaLE.LE()");
	    
	    for (i=0; i<t1; i++) {
	        v1[i] = new T1(i,x,monitor,i*500);
	        v1[i].start(); 
	     }
	     for (i=0; i<t2; i++) {
	        v2[i] = new T2(i,monitor,x,i*500);
	        v2[i].start(); 
	     }
	     for (i=0; i<t3; i++) {
		    v3[i] = new T3(i,monitor,x,i*500);
		    v3[i].start(); 
		 }
	}

}
