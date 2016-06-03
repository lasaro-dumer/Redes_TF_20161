#include "networkElement.hpp"
#include <string>
#include <map>
using namespace std;

void networkElement::addArpEntry(unsigned int ip,string mac){
    this->arpTable[ip] = mac;
}
string networkElement::getMacFromArpTable(unsigned int ip){
    if(this->arpTable.find(ip) != this->arpTable.end())
        return this->arpTable[ip];
    return nullptr;
}
