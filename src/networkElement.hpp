#ifndef netElemH
#define netElemH
#include <string>
#include <map>
#include <vector>
#include "ICMPPackage.hpp"
using namespace std;
class networkElement{
    string name,elemType;
    map<unsigned int,string> arpTable;
public:
    virtual ~networkElement(){};
    networkElement(string n,string et):name(n),elemType(et){};
    string getName(void){ return name;}
    string getType(void){ return elemType;}
    void addArpEntry(unsigned int ip,string mac);
    string getMacFromArpTable(unsigned int ip);
    virtual networkElement* getElementOrHopTo(ipv4* ip,ipv4& next_IP){};
    virtual int getMtuToNextHop(ipv4* ip){};
    virtual string doArpRequest(networkElement* nextHop,ipv4* dst_IP,bool print){};
    virtual bool hasIP(ipv4* ip){};
    virtual ipv4* getDefaultIP(){};
    virtual string getMacToPort(ipv4* portIP){};
    virtual string toString(){
        return this->name;
    }
};
#endif
