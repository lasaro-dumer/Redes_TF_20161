import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class Router{
	String name;
	int nports;
	ArrayList<Port> ports;
	public Map<String,TE> routerTable;
	ARP arp;
	ICMP icmp;

	public Router(String name,int nports){
		this.name = name;
		this.nports = nports;
		routerTable = new HashMap<String,TE>();
		ports = new ArrayList<Port>();
		arp = new ARP();
		icmp =  new ICMP();
	}

    public Port getPortByNumber(int portNumber){
        for (Port p : ports)
            if(p.number==portNumber)
                return p;
        return null;
    }

	public String getName(){
		return name;
	}

	public String toString(){
		String ret = name+","+nports;
		if(routerTable.size()>0){
			ret += "\n";
			for (TE te : routerTable.values()) {
				ret += te.toString();
			}
		}
		return ret;
	}
}
