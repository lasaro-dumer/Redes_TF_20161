#ifndef teH
#define teH
#include <string>
#include "port.hpp"
class te {
    string netDest,nextHop;
    port* p;
public:
    te():p(){};
    te(string n,string nxt,port* pt):netDest(n),nextHop(nxt){
        p = pt;
    }
    string getNetworkDest(){return netDest;}
    string getNextHop(){return nextHop;}
    port* getPort(){return p;}
    string toString();
};
#endif
