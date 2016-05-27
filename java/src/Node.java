public class Node{
	String name,
			MAC,
			IP,
			MTU,
			GATEWAY;
	ARP arp;
	ICMP icmp;

	public Node(String name,String MAC,String IP, String MTU, String GATEWAY){
		this.name = name;
		this.MAC = MAC;
		this.IP = IP;
		this.MTU = MTU;
		this.GATEWAY = GATEWAY;
		arp = new ARP();
		icmp =  new ICMP();
	}

	public String getName(){
		return name;
	}

	public String toString(){
		return name+","+MAC+","+IP+","+MTU+","+GATEWAY;
	}
}
