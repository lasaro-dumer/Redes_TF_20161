#include <string>
#include "node.hpp"
using namespace std;

string node::toString(){
    stringstream ss;
    ss << this->getName() << "," << this->p->toString() << "," << gateway;
    if(gatewayObj != nullptr)
        ss << " ["<< gatewayObj->getName() <<"]";
    return ss.str();
}
