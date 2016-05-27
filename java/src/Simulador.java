import java.util.List;

public class Simulador{
	String file , origem, destino,mensagem;
	public static void main(String[] args){
		try{
			//topologia.txt n1 n2 hello
			String filename = args[0];
			String n1 = args[1];
			String n2 = args[2];
			String m = args[3];
			Reader r = new Reader();

			List<Object> elements = r.read(filename);

			Object current = elements.get(0);


			//Defini método dentro de Node e Router para pegar o nome do dois, aqui quero validar a partir do nome em quem eu estou para garantir que  o pacote chegara no final.
			/*
			while(current.getName().equals(n2)){
				if(current instanceof  Node){
					se current = node
						procura na tabela arp
							se verdade retorna MAC
							senão exeuta arp -> executa icmp
				}else{
					se current = router
					 	procura na tabela de roteamento
							se tiver em local manda pro node
							se nao manda pro proximo
				}
			}*/

			for (Object obj : elements) {
				if(obj instanceof  Node){
					System.out.println("NOOODO");
				}
				System.out.println(obj.toString());
			}
		}
		catch(Exception e){
			System.out.println("Error: " + e.getMessage());
			e.printStackTrace();
		}
	}
}
