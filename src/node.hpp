#ifndef nodeH
#define nodeH
#include <string>
#include <sstream>
#include <iostream>
#include "networkElement.hpp"
#include "port.hpp"
#include "ipv4.hpp"
#include "router.hpp"

using namespace std;

class node : public networkElement{
	string gateway;
	port* p;
	networkElement* gatewayObj;
public:
	node(string n,string m,string i,int mt,string g):networkElement(n,"node"),gateway(g){
		p=new port(m,i,mt,1);
		gatewayObj = nullptr;
	}
	node(string n,port* pt,string g):networkElement(n,"node"),p(pt),gateway(g){}
	string getIPAsHumanReadable(void) { return this->p->getIPAsHumanReadable(); }
	ipv4* getIP(void) { return this->p->getIP(); }
	bool hasIP(ipv4* ip);
	string getMAC(void) { return this->p->getMAC(); }
	networkElement* getElementOrHopTo(ipv4* ip,ipv4& next_IP);
	string doArpRequest(networkElement* nextHop,ipv4* dst_IP,bool print);
	int getMtuToNextHop(ipv4* ip){ return p->getMTU(); }
	string getMacToPort(ipv4* portIP);
	ipv4* getDefaultIP(){ return this->getIP(); }
	int getMTU(void){ return this->p->getMTU(); }
	string getGatewayIP(void) { return this->gateway; }
	networkElement* setGateway(networkElement* gatewayObject){ this->gatewayObj = gatewayObject;}
	networkElement* getGateway(){ return this->gatewayObj;}
	string toString();
};
#endif
