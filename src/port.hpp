#ifndef portH
#define portH
#include <string>
#include <sstream>
#include "ipv4.hpp"
using namespace std;
class port{
    string mac;
    int mtu,portNum;
    ipv4* ip;
public:
    port(void):portNum(-1){};
    port(string m,string i,int mt,int num):mac(m),mtu(mt),portNum(num){
        ip = new ipv4(i);
    };
    //port& operator=( const port& p );
	string getIPAsHumanReadable(void) { return this->ip->getAsHumanReadable(); }
	ipv4* getIP(void) { return this->ip; }
	string getMAC(void) { return this->mac; }
	int getMTU(void){ return this->mtu; }
    int getPortNumber(void){return this->portNum;}
    string toString();
};
#endif
