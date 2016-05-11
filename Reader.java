import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Reader{
	public String read(String file){
		try(BufferedReader br = new BufferedReader(new FileReader(file))) {
    		StringBuilder sb = new StringBuilder();
    		String line = br.readLine();

    		while (line != null) {
        		sb.append(line);
        		sb.append(System.lineSeparator());
        		line = br.readLine();
    		}
    		String everything = sb.toString();
		}catch (IOException e) {
			e.printStackTrace();
		} 
	}
}