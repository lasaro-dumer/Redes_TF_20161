#ifndef routerH
#define routerH
#include <string>
#include "networkElement.hpp"
#include "port.hpp"
#include "te.hpp"
#include <vector>
#include <map>

using namespace std;
class router: public networkElement{
    int nPorts;
    map<int,port*> ports;
    map<unsigned int,te*> routerTable;
    map<unsigned int,vector<networkElement*>> networks;
public:
    virtual ~router(){};
    router(string n,int p):networkElement(n,"router"),nPorts(p){};
    int getNumPorts(void){return this->nPorts;}
    port* getPortByNumber(int pn);
    void addPort(port* p);
    void addRouterTableEntry(te* t);
    void connectElement(networkElement* n);
    bool belongsToNetwork(ipv4* networkIp);
    bool hasIP(ipv4* ip);
    string toString();
};
#endif
