#include <string>
#include "te.hpp"
using namespace std;

string te::getNextHopIP(){
    return this->nextHop;
}

string te::toString(){
    stringstream ss;
    ss << this->getNetworkDest() << " | " << this->getNextHopIP() << " : " << this->getPort()->getPortNumber();
    return ss.str();
}
