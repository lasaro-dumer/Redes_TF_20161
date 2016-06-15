#ifndef ipv4H
#define ipv4H
#include <string>
using namespace std;
class ipv4 {
private:
    string ip_v4;
    bool bCalculated,bReadable;
    unsigned int asBits;
public:
    ipv4(){
        this->asBits=0;
        this->bCalculated=false;
        this->bReadable=false;
    };
    ipv4(string ip):ip_v4(ip){
        this->asBits=0;
        this->bCalculated=false;
        this->bReadable=true;
        asBits = this->getAsBits();
    };
    ipv4(unsigned int ip){
        this->asBits=ip;
        this->bCalculated=true;
        this->bReadable=false;
        ip_v4 = this->getAsHumanReadable();
    };
    unsigned int getAsBits();
    string getAsBitsString();
    string getAsHumanReadable();
};
#endif
