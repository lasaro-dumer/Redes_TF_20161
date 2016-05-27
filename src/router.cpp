#include "router.hpp"
#include "port.hpp"
#include "te.hpp"
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
    this->routerTable[t->getNetworkDest()] = t;
}

string router::toString(){
    stringstream ss;
    ss << this->getName() << "," << nPorts;
    map<int,port*>::iterator i;
    for(i=ports.begin(); i != ports.end(); ++i){
        ss << "," << (*i).second->toString();
    }
    map<string,te*>::iterator ii;
    for(ii=routerTable.begin(); ii!=routerTable.end(); ++ii)
    {
        ss << endl <<(*ii).first << ": " << (*ii).second->toString();
    }
    return ss.str();
}
