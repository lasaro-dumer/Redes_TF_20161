#include <string>
#include "node.hpp"
using namespace std;

string node::toString(){
    stringstream ss;
    ss << this->getName() << "," << this->p->toString() << "," << gateway;
    #ifdef DEBUG
    if(gatewayObj != nullptr)
        ss << " ["<< gatewayObj->getName() <<"]";
    #endif
    return ss.str();
}
