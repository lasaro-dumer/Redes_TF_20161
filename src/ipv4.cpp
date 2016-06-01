#include "ipv4.hpp"
#include "util.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <iomanip>
//std::string ss = std::bitset< 64 >( 12345 ).to_string(); // string conversion
//std::cout << std::bitset<64>( 54321 ) << ' '; // direct output

using namespace std;

unsigned int ipv4::getAsBits(){
    if(!this->bCalculated){
        this->asBits = ipv4AsBits(this->ip_v4);
        this->bCalculated=true;
    }
    return this->asBits;
}
string ipv4::getAsBitsString(){
    return ipv4AsBitsString(this->getAsBits());
}
string ipv4::getAsHumanReadable(){
    if(!this->bReadable){
        this->ip_v4 = ipv4AsHumanReadable(this->asBits);
        this->bReadable=true;
    }
    return this->ip_v4;
}
