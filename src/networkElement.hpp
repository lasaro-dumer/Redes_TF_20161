#ifndef netElemH
#define netElemH
#include <string>
#include <map>
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
    virtual string toString(){
        return this->name;
    }
};
#endif
