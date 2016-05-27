public class Port{
	String MAC,
			IP,
			MTU;
	public int number;
	public Port(String mac,String IP,String MTU){
		this.MAC = mac;
		this.IP = IP;
		this.MTU = MTU;
	}

	public String toString(){
		return ""+number;
	}
}
