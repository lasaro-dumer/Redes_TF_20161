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
    map<string,te*> routerTable;
public:
    virtual ~router(){};
router(string n,int p):networkElement(n,"router"),nPorts(p){};
    int getNumPorts(void){return this->nPorts;}
    port* getPortByNumber(int pn);
    void addPort(port* p);
    void addRouterTableEntry(te* t);
    string toString();
};
#endif
