#ifndef ipv4H
#define ipv4H
#include <string>
using namespace std;
class ipv4 {
private:
    string ip_v4;
    int bCalculated;
    unsigned int asBits;
public:
    ipv4(string ip):ip_v4(ip){
        this->asBits=0;
        this->bCalculated=0;
        asBits = this->getAsBits();
    };
    unsigned int getAsBits();
    string getAsBitsString();
    string getAsHumanReadable();
};
#endif
