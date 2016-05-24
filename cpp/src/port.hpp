#ifndef portH
#define portH
#include <string>
#include <sstream>
using namespace std;
class port{
    string ip,mac;
    int mtu,portNum;
public:
    port(void):portNum(-1){};
    port(string m,string i,int mt,int num):ip(i),mac(m),mtu(mt),portNum(num){};
    //port& operator=( const port& p );
	string getIP(void) { return this->ip; }
	string getMAC(void) { return this->mac; }
	int getMTU(void){ return this->mtu; }
    int getPortNumber(void){return this->portNum;}
    string toString();
};
#endif
