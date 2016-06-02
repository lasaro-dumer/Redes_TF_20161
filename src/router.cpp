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
