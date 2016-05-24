#include "port.hpp"
using namespace std;
/*
port& port::operator=( const port& p )
{
    mac = p.mac;
    ip = p.ip;
    mtu = p.mtu;
    return *this;
}
//*/
string port::toString(){
    stringstream ss;
    ss << this->mac << ","<< this->ip << "," << this->mtu;
    return ss.str();
}
