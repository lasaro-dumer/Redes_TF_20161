import java.util.*;

public class ARP{

	Map<String,String> arpTable;

	public ARP(){
		arpTable =  new HashMap<String,String>();
	}

	public String request(String sn,String dip,String sip){
		//Pacotes ARP Request: <src_name> box <src_name> : ARP - Who has <dst_IP>? Tell <src_IP>;
		return null;
	}

	public String reply(){
		//Pacotes ARP Reply: <src_name> => <dst_name> : ARP - <src_IP> is at <src_MAC>;
		return null;
	}

	public String searchArpTable(String ip){
		String mac = null;
		if(arpTable.containsKey(ip)){
			mac = arpTable.get(ip);
		}

		return mac;
	}
}
