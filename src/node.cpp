#include <string>
#include <iostream>
#include "node.hpp"
#include "router.hpp"
using namespace std;

bool node::hasIP(ipv4* ip){
    return p->getIP()->getAsBits() == ip->getAsBits();
}

string node::getMacToPort(ipv4* portIP){
    if(portIP->getAsBits() == p->getIP()->getAsBits())
        return p->getMAC();
    return "";
}
networkElement* node::getElementOrHopTo(ipv4* ip,ipv4& next_IP){
    networkElement* next = gatewayObj;
    next_IP = *(new ipv4(gateway));
    //to make sure we have something
    if(gatewayObj != nullptr && gatewayObj->getType() == "router"){
        router* r = (router*)gatewayObj;
        next = r->getElementFromLAN(getIP(),ip);
        if(next != nullptr){
            next_IP = *ip;
        }else{
            next = gatewayObj;
        }
    }
    return next;
}

string node::doArpRequest(networkElement* nextHop,ipv4* dst_IP,bool print=false){
    string srcName = getName();
    string dstName = nextHop->getName();
    string dstIP = dst_IP->getAsHumanReadable();
    string srcIP = getIP()->getAsHumanReadable();

    string mac;
    if(nextHop->getType() == "router" && !nextHop->hasIP(dst_IP)){
        router* r = (router*)nextHop;
        networkElement* el = r->getElementFromLAN(getIP(),dst_IP);
        mac = el->getMacToPort(dst_IP);
        dstName = el->getName();
        el->addArpEntry(getIP()->getAsBits(),getMAC());
        r->addArpEntry(dst_IP->getAsBits(),mac);
    }else{
        mac = nextHop->getMacToPort(dst_IP);
    }
    nextHop->addArpEntry(getIP()->getAsBits(),getMAC());
    addArpEntry(dst_IP->getAsBits(),mac);
    if(print){
        //Pacotes ARP Request: <src_name> box <src_name> : ARP - Who has <dst_IP>? Tell <src_IP>;
        cout << srcName << " box " << srcName << " : ARP - Who has " << dstIP << "? Tell " << srcIP << ";" << endl;
        //Pacotes ARP Reply: <src_name> => <dst_name> : ARP - <src_IP> is at <src_MAC>;
        cout << dstName << " => " << srcName << " : ARP - " << dstIP << " is at " << mac << ";" << endl;
    }

    return mac;
}

string node::toString(){
    stringstream ss;
    ss << this->getName() << "," << this->p->toString() << "," << gateway;
    #ifdef DEBUG
    if(gatewayObj != nullptr)
        ss << " ["<< gatewayObj->getName() <<"]";
    #endif
    return ss.str();
}
