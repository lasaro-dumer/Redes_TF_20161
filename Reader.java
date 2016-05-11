package TF;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Reader{
	public String read(String file){
		StringBuilder sb = new StringBuilder();
		try(BufferedReader br = new BufferedReader(new FileReader(file))) {
    		String line = br.readLine();
    		while (line != null) {
        		sb.append(line);
        		sb.append(System.lineSeparator());
        		line = br.readLine();
    		}
		}catch (IOException e) {
			e.printStackTrace();
		}
		return sb.toString();
	}
}