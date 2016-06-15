#include "ipv4.hpp"
#include "ICMPPackage.hpp"
#include <string>
#include <sstream>
#include <vector>

void ICMPPackage::updateDataLinkInfo(string srcHopName,string srcHopMAC,string dstHopName,string dstHopMAC){
    this->srcHop_Name = srcHopName;
    this->srcHop_MAC = srcHopMAC;
    this->dstHop_Name = dstHopName;
    this->dstHop_MAC = dstHopMAC;
}

string ICMPPackage::toString(){
    stringstream ss;
    if(type == "request"){
        //Pacotes ICMP Echo Request: <src_name> => <dst_name> : ICMP - Echo (ping) request (src=<src_IP> dst=<dst_IP> ttl=<TTL> data=<msg>);
        ss << srcHop_Name << " => " << dstHop_Name << " : ICMP - Echo (ping) request (src=" << src_IP->getAsHumanReadable() << " dst=" << dst_IP->getAsHumanReadable() << " ttl=" << TTL << " data=" << message << ");";
    }else{
        //Pacotes ICMP Echo Reply: <src_name> => <dst_name> : ICMP - Echo (ping) reply (src=<src_IP> dst=<dst_IP> ttl=<TTL> data=<msg>);
        ss << srcHop_Name << " => " << dstHop_Name << " : ICMP - Echo (ping) reply (src=" << src_IP->getAsHumanReadable() << " dst=" << dst_IP->getAsHumanReadable() << " ttl=" << TTL << " data=" << message << ");";
    }
    return ss.str();
}
