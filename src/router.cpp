#include "router.hpp"
#include "port.hpp"
#include "te.hpp"
#include "util.hpp"
#include "node.hpp"
#include <iostream>
#include <sstream>
using namespace std;

port* router::getPortByNumber(int pn){
    map<int,port*>::iterator it = ports.find(pn);
    if(it != ports.end())
        return (*it).second;
    return nullptr;
}

void router::addPort(port* p) {
    this->ports[p->getPortNumber()]=p;
}

void router::addRouterTableEntry(te* t){
    unsigned int ip = ipv4AsBits(t->getNetworkDest());
    unsigned int net = getNetworkFromIp(ip);
    this->routerTable[net] = t;
}

bool router::belongsToNetwork(ipv4* networkIp){
    map<int,port*>::iterator i;
    unsigned int net = networkIp->getAsBits();
    for(i=ports.begin(); i != ports.end(); ++i){
        if(areSameNetwork(net,(*i).second->getIP()->getAsBits()))
            return true;
    }
    return false;
}

bool router::hasIP(ipv4* ip){
    map<int,port*>::iterator i;
    for(i=ports.begin(); i != ports.end(); ++i){
        if((*i).second->getIP()->getAsBits() == ip->getAsBits())
            return true;
    }
    return false;
}

void router::connectElement(networkElement* ne){
    map<int,port*>::iterator ps;
    //unsigned int elemIp = n->getIP()->getAsBits();
    if(ne->getType() == "node"){
        for (ps = ports.begin(); ps != ports.end(); ++ps) {
            port* p = (port*)(*ps).second;
            unsigned int net = getNetworkFromIp(p->getIP()->getAsBits());
            //std::cout << "network: "<<ipv4AsHumanReadable(net)  << " for ip: " << p->getIP()->getAsHumanReadable() << std::endl;
            node* n = (node*)ne;
            if(areSameNetwork(net,n->getIP()->getAsBits())){
                if(networks.find(net) != networks.end()){
                    networks[net].push_back(ne);
                }else{
                    vector<networkElement*> v;
                    v.push_back(ne);
                    networks[net] = v;
                }
                n->setGateway(this);
            }
        }
    }else if(ne->getType() == "router"){
        //std::cout << "connecting router" << std::endl;
        router* r = (router*)ne;
        map<unsigned int,te*>::iterator ii;
        for(ii=routerTable.begin(); ii!=routerTable.end(); ++ii)
        {
            te* entry = (*ii).second;
            string ip = entry->getNextHopIP();
            if(ip=="0.0.0.0"){
                ipv4* eIp = new ipv4(entry->getNetworkDest());
                if(r->belongsToNetwork(eIp)){
                    //std::cout << "r["<<r->getName()<<"] belongsToNetwork ["<< eIp->getAsHumanReadable() <<"] in ["<< this->getName() <<"]" << std::endl;
                    unsigned int net = getNetworkFromIp(eIp->getAsBits());
                    //std::cout << "network: "<<ipv4AsHumanReadable(net)  << " for ip: " << eIp->getAsHumanReadable() << std::endl;
                    if(networks.find(net) != networks.end()){
                        networks[net].push_back(ne);
                    }else{
                        vector<networkElement*> v;
                        v.push_back(ne);
                        networks[net] = v;
                    }
                }
            }else if(r->hasIP(new ipv4(ip))){
                //std::cout << "r["<<r->getName()<<"] has ip from entry ["<<entry->toString()<<"] from r["<<this->getName()<<"]" << std::endl;
                entry->setNextHop(r);
            }
        }
    }
}

string router::toString(){
    stringstream ss;
    ss << this->getName() << "," << nPorts;
    map<int,port*>::iterator i;
    for(i=ports.begin(); i != ports.end(); ++i){
        ss << "," << (*i).second->toString();
    }
    map<unsigned int,te*>::iterator ii;
    for(ii=routerTable.begin(); ii!=routerTable.end(); ++ii)
    {
        ss << endl;
        #ifdef DEBUG
        ss << (*ii).second->getNetworkDest() << ": ";
        #endif
        ss << (*ii).second->toString();
    }
    #ifdef DEBUG
    map<unsigned int,vector<networkElement*>>::iterator nets;
    for (nets = networks.begin(); nets != networks.end(); ++nets) {
        ss << endl << "\t["<< ipv4AsHumanReadable((*nets).first) << "]";
        vector<networkElement*> es = (*nets).second;
        vector<networkElement*>::iterator esi;
        for(esi=es.begin(); esi!=es.end(); ++esi)
        {
            ss << endl << "\t\t" << (*esi)->getName();
        }
    }
    #endif
    return ss.str();
}

string router::doArpRequest(networkElement* nextHop,ipv4* dst_IP,bool print=false){
    string srcName = getName();
    string dstName = nextHop->getName();
    string dstIP = dst_IP->getAsHumanReadable();
    ipv4* src_IP = getIpToNextHop(dst_IP);
    string src_MAC = getMacToPort(src_IP);
    string srcIP = src_IP->getAsHumanReadable();

    string mac;
    if(nextHop->getType() == "router" && !nextHop->hasIP(dst_IP)){
        std::cout << "unexcpected error" << std::endl;
        /*
        router* r = (router*)nextHop;
        networkElement* el = r->getElementFromLAN(getIP(),dst_IP);
        mac = el->getMacToPort(dst_IP);
        dstName = el->getName();
        el->addArpEntry(getIP()->getAsBits(),getMAC());
        r->addArpEntry(getIP()->getAsBits(),getMAC());
        r->addArpEntry(dst_IP->getAsBits(),mac);
        //*/
    }else{
        mac = nextHop->getMacToPort(dst_IP);
    }
    nextHop->addArpEntry(src_IP->getAsBits(),src_MAC);
    addArpEntry(dst_IP->getAsBits(),mac);

    if(print){
        //Pacotes ARP Request: <src_name> box <src_name> : ARP - Who has <dst_IP>? Tell <src_IP>;
        cout << srcName << " box " << srcName << " : ARP - Who has " << dstIP << "? Tell " << srcIP << ";" << endl;
        //Pacotes ARP Reply: <src_name> => <dst_name> : ARP - <src_IP> is at <src_MAC>;
        cout << dstName << " => " << srcName << " : ARP - " << dstIP << " is at " << mac << ";" << endl;
    }

    return mac;
}

networkElement* router::getElementFromLAN(ipv4* src_IP,ipv4* dst_IP){
    if(areSameNetwork(src_IP->getAsBits(),dst_IP->getAsBits())){
        unsigned int net = getNetworkFromIp(dst_IP->getAsBits());
        if(networks.find(net) != networks.end()){
            vector<networkElement*> elems = networks[net];
            vector<networkElement*>::iterator esi;
            for(esi=elems.begin(); esi!=elems.end(); ++esi)
                if((*esi)->hasIP(dst_IP))
                    return (*esi);
        }
    }
    return nullptr;
}

string router::getMacToPort(ipv4* portIP){
    map<int,port*>::iterator i;
    for(i=ports.begin(); i != ports.end(); ++i)
        if((*i).second->getIP()->getAsBits() == portIP->getAsBits())
            return (*i).second->getMAC();
    return "";
}

te* router::getTableEntryToIp(ipv4* ip){
    unsigned int net = getNetworkFromIp(ip->getAsBits());
    map<unsigned int,te*>::iterator ii;
    for(ii=routerTable.begin(); ii!=routerTable.end(); ++ii)
        if(areSameNetwork((*ii).first,net))
            return (*ii).second;
    //get default route
    unsigned int defaultRouteNet = 0;
    if(routerTable.find(defaultRouteNet) != routerTable.end())
        return routerTable[defaultRouteNet];
    return nullptr;
}

int router::getMtuToNextHop(ipv4* ip){
    te* entry = this->getTableEntryToIp(ip);
    if(entry != nullptr)
        return entry->getPort()->getMTU();
    return -1;
}

ipv4* router::getIpToNextHop(ipv4* ip){
    te* entry = this->getTableEntryToIp(ip);
    if(entry != nullptr)
        return entry->getPort()->getIP();
    return nullptr;
}

networkElement* router::getElementOrHopTo(ipv4* ip,ipv4& next_IP){
    unsigned int net = getNetworkFromIp(ip->getAsBits());
    map<unsigned int,te*>::iterator ii;
    for(ii=routerTable.begin(); ii!=routerTable.end(); ++ii)
    {
        if(areSameNetwork((*ii).first,net)){
            te* entry = (*ii).second;
            if(entry->getNextHopIP()=="0.0.0.0"){
                //direct connection to network, just get the element from networks map
                if(networks.find(net) != networks.end()){
                    vector<networkElement*> elems = networks[net];
                    vector<networkElement*>::iterator esi;
                    for(esi=elems.begin(); esi!=elems.end(); ++esi)
                        if((*esi)->hasIP(ip)){
                            if((*esi)->getType()== "node")
                                next_IP = *((node*)*esi)->getIP();
                            else
                                next_IP = *(new ipv4(ip->getAsHumanReadable()));
                            return (*esi);
                        }
                }
                //failed... return nullptr      , BUT should never get here...
                std::cout << "Fatal ERROR !!!! :'(" << std::endl;
                //exit(-1);
                return nullptr;
            }else{
                next_IP = *(new ipv4(entry->getNextHopIP()));
                return entry->getNextHop();
            }
        }
    }
    //get default route...
    unsigned int defaultRouteNet = 0;
    if(routerTable.find(defaultRouteNet) != routerTable.end()){
        te* entry = routerTable[defaultRouteNet];
        next_IP = *(new ipv4(entry->getNextHopIP()));
        return entry->getNextHop();
    }
    return nullptr;
}
