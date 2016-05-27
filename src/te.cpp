#include <string>
#include "te.hpp"
using namespace std;

string te::toString(){
    stringstream ss;
    ss << this->getNetworkDest() << " | " << this->getNextHop() << " : " << this->getPort()->getPortNumber();
    return ss.str();
}
