package TF;

public class Simulador{
	String file , origem, destino,mensagem;
	public static void main(String file,String origem,String destino,String mensagem){
		this.file = file;
		this.origem = origem;
		this.destino = destino;
		this.mensagem = mensagem;

		Reader r = new Reader();
		r.read(file);
	}
}