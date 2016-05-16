import java.util.ArrayList;
import java.util.Collections; 
import java.util.HashMap;
import java.util.Map;

public class Router{
	String name;
	int nports;
	ArrayList<Port> ports;
	Map<String,TE> routerTable;

	public Router(){
		routerTable = new HashMap<String,TE>();
		ports = new ArrayList<Port>();
	}

}
