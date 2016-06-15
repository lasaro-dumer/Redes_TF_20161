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
    te* getTableEntryToIp(ipv4* ip);
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
    networkElement* getElementOrHopTo(ipv4* ip,ipv4& next_IP);
    string doArpRequest(networkElement* nextHop,ipv4* dst_IP,bool print);
    int getMtuToNextHop(ipv4* ip);
    ipv4* getIpToNextHop(ipv4* dst_IP);
    string getMacToPort(ipv4* portIP);
    networkElement* getElementFromLAN(ipv4* src_IP,ipv4* dst_IP);
    string toString();
};
#endif
