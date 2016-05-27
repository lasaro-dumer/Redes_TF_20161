import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Optional;

public class Reader{
	private 	List<Object> networkObjects;
	public Reader(){
	 networkObjects = new ArrayList<Object>();

	}

	public List<Object> read(String file) throws Exception{
		EntryType type = EntryType.Node;
		StringBuilder sb = new StringBuilder();

		try(BufferedReader br = new BufferedReader(new FileReader(file))) {
    		String line = br.readLine();
    		while (line != null) {
				line = line.toUpperCase();
				if(line.equals("#NODE")){
					type=EntryType.Node;
				}else if(line.equals("#ROUTER")){
					type=EntryType.Router;
				}else if(line.equals("#ROUTERTABLE")){
					type=EntryType.RouterTable;
				}else{
					Object obj = parseLine(line,type);
					//System.out.println("parsed:"+line);
					if(obj != null)
						networkObjects.add(obj);
				}
				sb.append(line);
        		sb.append(System.lineSeparator());
        		line = br.readLine();
    		}
		}catch (IOException e) {
			e.printStackTrace();
		}

		//System.out.println(sb.toString());
		return networkObjects;
	}

	private Object parseLine(String line,EntryType type) throws Exception{
		StringTokenizer st = new StringTokenizer(line, ",");
		Object element = null;
		switch (type) {
			case Node:
				element = new Node(st.nextToken().trim(),
									st.nextToken().trim(),
									st.nextToken().trim(),
									st.nextToken().trim(),
									st.nextToken().trim());
				break;
			case Router:
				element = new Router(st.nextToken().trim(),Integer.parseInt(st.nextToken().trim()));
				int pNumber = 0;
				while(st.hasMoreElements()){
					Port port = new Port(st.nextToken().trim(),
										st.nextToken().trim(),
										st.nextToken().trim());
					port.number = pNumber;
					pNumber++;
					((Router)element).ports.add(port);
				}
				break;
			case RouterTable:
				String routerName = st.nextToken().trim();
				String netDest =st.nextToken().trim();
				String nextHop =st.nextToken().trim();
				int portNumber=Integer.parseInt(st.nextToken().trim());
				Router router = getRouterByName(routerName);
				if(router != null){
					Port port = router.getPortByNumber(portNumber);
					if(port!=null){
						TE entry = new TE(netDest,nextHop,port);
						router.routerTable.put(entry.dest,entry);
					}
				}
				break;
			default:
				throw new Exception("Error reading file.");
		}

		return element;
	}
	private Router getRouterByName(String name){
        Optional<Object> opt = networkObjects
                                            .stream()
                                            .filter(e -> e instanceof Router && ((Router)e).name.equals(name)).findFirst();
        if(opt.isPresent())
            return (Router)opt.get();
        return null;
    }

	public enum EntryType{
		Node("#NODE"),Router("#ROUTER"),RouterTable("#ROUTERTABLE");
		private final String tipo;
		EntryType(String tipo){
			this.tipo = tipo;
		}

		public String getTipo(){
			return tipo;
		}
	}
}
