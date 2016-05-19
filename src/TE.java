public class TE{
	String dest,
			nexthop;
	Port port;

	public TE(String net_dest,String nexthop, Port port){
		this.dest = net_dest;
		this.nexthop = nexthop;
		this.port = port;
	}

	public String toString(){
		return dest+","+nexthop+","+port;
	}
}
