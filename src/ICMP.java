public class ICMP{

	public ICMP(){

	}

	public String request(String sn,String dn,String sip,String dip,int ttl,String m){
		//Pacotes ICMP Echo Request: <src_name> => <dst_name> : ICMP - Echo (ping) request (src=<src_IP> dst=<dst_IP> ttl=<TTL> data=<msg>);
		return null;
	}

	public String reply(){
		//Pacotes ICMP Echo Reply: <src_name> => <dst_name> : ICMP - Echo (ping) reply (src=<src_IP> dst=<dst_IP> ttl=<TTL> data=<msg>);
		return null;
	}
}
