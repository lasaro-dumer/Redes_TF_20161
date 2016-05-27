#ifndef netElemH
#define netElemH
#include <string>
using namespace std;
class networkElement{
    string name,elemType;
public:
    virtual ~networkElement(){};
    networkElement(string n,string et):name(n),elemType(et){};
    string getName(void){ return name;}
    string getType(void){ return elemType;}
    virtual string toString(){
        return this->name;
    }
};
#endif
