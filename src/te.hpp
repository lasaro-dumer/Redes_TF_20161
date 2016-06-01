#ifndef teH
#define teH
#include <string>
#include "port.hpp"
#include "networkElement.hpp"
class te {
    string netDest,nextHop;
    networkElement* nextHopObj;
    port* p;
public:
    te():p(){};
    te(string n,string nxt,port* pt):netDest(n),nextHop(nxt){
        p = pt;
        nextHopObj = nullptr;
    }
    string getNetworkDest(void){return this->netDest;}
    string getNextHopIP(void);
    void setNextHop(networkElement* nh){ this->nextHopObj = nh; }
    networkElement* getNextHop(){ return this->nextHopObj; }
    port* getPort(){return p;}
    string toString();
};
#endif
