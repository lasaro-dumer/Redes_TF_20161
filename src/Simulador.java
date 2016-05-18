public class Simulador{
	String file , origem, destino,mensagem;
	public static void main(String[] args){
		String filename = args[0];
		//String n1 = origem;
		//String n2 = destino;
		///String m = mensagem;

		Reader r = new Reader();
		System.out.println(r.read(filename));
	}
}
