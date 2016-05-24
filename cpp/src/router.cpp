#include "router.hpp"
#include "port.hpp"
#include "te.hpp"
#include <iostream>
#include <sstream>
using namespace std;

port* router::getPortByNumber(int pn){
    vector<port*>::iterator i;
    port* p;
    for(i=ports.begin(); i != ports.end(); ++i){
        if ((*i)->getPortNumber() == pn) {
            return *i;
        }
    }
    return p;
}

void router::addPort(port* p) {
    this->ports.push_back(p);
}

void router::addRouterTableEntry(te* t){
    this->routerTable[t->getNetworkDest()] = t;
}

string router::toString(){
    stringstream ss;
    ss << this->getName() << "," << nPorts;
    vector<port*>::iterator i;
    for(i=ports.begin(); i != ports.end(); ++i){
        ss << "," << (*i)->toString();
    }
    map<string,te*>::iterator ii;
    for(ii=routerTable.begin(); ii!=routerTable.end(); ++ii)
    {
        ss << endl <<(*ii).first << ": " << (*ii).second->toString();
    }
    return ss.str();
}
