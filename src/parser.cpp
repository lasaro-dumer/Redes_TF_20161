#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.hpp"
#include "util.hpp"
#include "node.hpp"
#include "router.hpp"
#include "port.hpp"
#include "te.hpp"

using namespace std;

void parser::parseFile(char* fileName){
    locale loc;
    string line;
    vector<string> s;
    ifstream myReadFile;
    myReadFile.open(fileName);
    int state = 0;
    while(!safeGetline(myReadFile, line).eof())// To get you all the lines.
    {
        //std::cout << "getting line.." << std::endl;
        //getline(myReadFile,line); // Saves the line in line.
        //std::cout << "got line " << line << std::endl;
        if(!line.empty()){
            line = tolowercase(line);
            //cout << line << endl; // Prints our line.
            if (line == "#node") {
                state=1;
            }else if (line == "#router") {
                state=2;
            }else if (line == "#routertable") {
                state=3;
            }else if(1 <= state && state <= 3){
                s = split(line,',');
                switch (state) {
                    case 1:
                        {
                            string name = s[0];
                            string mac = s[1];
                            string ip = s[2];
                            int mtu = stoi(s[3],nullptr,10);
                            string gateway = s[4];
                            node* n = new node(name,mac,ip,mtu,gateway);
                            //this->netNodes.push_back(n);
                            this->networkObjects.push_back(n);
                            //std::cout << "n="<<n->toString() << std::endl;
                            break;
                        }
                    case 2:
                        {
                            string name = s[0];
                            int nPorts = stoi(s[1],nullptr,10);
                            router* r = new router(name,nPorts);
                            int pn=0;
                            for (int i = 2; i < s.size(); i=i+3) {
                                string mac = s[i];
                                string ip = s[i+1];
                                int mtu = stoi(s[i+2],nullptr,10);
                                port* p = new port(mac,ip,mtu,pn);
                                r->addPort(p);
                                pn++;
                            }
                            //this->netRouters.push_back(r);
                            this->networkObjects.push_back(r);
                            //std::cout << "r="<<r->toString() << std::endl;
                            break;
                        }
                    case 3:
                        {
            				string routerName = s[0];
            				string netDest =s[1];
            				string nextHop =s[2];
            				int portNumber=stoi(s[3],nullptr,10);
                            router* r = this->getRouterByName(routerName);
                            if(r != nullptr){
                                port* p= r->getPortByNumber(portNumber);
                                if(p != nullptr){
                                    te* entry = new te(netDest,nextHop,p);
                                    r->addRouterTableEntry(entry);
                                }
                                //std::cout << r->getName() << " line = " << line << std::endl;
                            }
                            break;
                        }
                    default:
                        break;
                }
            }
        }
    }
    //std::cout << "closing file" << std::endl;
	myReadFile.close();
    this->tuneNetwork();
}

void parser::tuneNetwork(){
    //std::cout << "tunning" << std::endl;
    vector<networkElement*>::iterator noi;
    for (noi = this->networkObjects.begin(); noi != this->networkObjects.end(); ++noi) {
        if((*noi)->getType()=="node"){
            node* n = ((node*)*noi);
            router* gateway = this->getRouterByIp(new ipv4(n->getGatewayIP()));
            if(gateway != nullptr){
                gateway->connectElement(n);
                #ifdef DEBUG
                if(n->getGateway() == nullptr)
                    std::cout << "error on connecting node and router gateway" << std::endl;
                else
                    std::cout << "connection successful between ["<<n->getName()<<"] and ["<<n->getGateway()->getName()<<"]" << std::endl;
                #endif
            }
        }else if((*noi)->getType()=="router"){
            router* r = ((router*)*noi);
            vector<router*> rs = this->getRouters();
            vector<router*>::iterator rsi;
            for (rsi = rs.begin(); rsi != rs.end(); ++rsi) {
                if(r->getName() != (*rsi)->getName())
                    r->connectElement(*rsi);
            }
        }
    }
}

router* parser::getRouterByIp(ipv4* ip){
    vector<networkElement*>::iterator noi;
    for (noi = this->networkObjects.begin(); noi != this->networkObjects.end(); ++noi) {
        if((*noi)->getType()=="router"){
            router* r = (router*)*noi;
            if(r->hasIP(ip))
                return r;
        }
    }
    return nullptr;
}

vector<node*> parser::getNodes(){
    vector<node*> nodes;
    vector<networkElement*>::iterator noi;
    for (noi = this->networkObjects.begin(); noi != this->networkObjects.end(); ++noi) {
        if((*noi)->getType()=="node"){
            nodes.push_back(dynamic_cast<node*>((*noi)));
        }
    }
    return nodes;
}

vector<router*> parser::getRouters(){
    vector<router*> routers;
    vector<networkElement*>::iterator noi;
    for (noi = this->networkObjects.begin(); noi != this->networkObjects.end(); ++noi) {
        if((*noi)->getType()=="router"){
            routers.push_back(dynamic_cast<router*>((*noi)));
        }
    }
    return routers;
}

networkElement* parser::getElementByName(string name,string type){
    vector<networkElement*>::iterator noi;
    for (noi = this->networkObjects.begin(); noi != this->networkObjects.end(); ++noi) {
        if((type=="any" || (*noi)->getType()==type)
            && (*noi)->getName()==name){
            return *noi;
        }
    }
    return nullptr;
}

router* parser::getRouterByName(string name){
    return dynamic_cast<router*>(this->getElementByName(name,"router"));
}

node* parser::getNodeByName(string name){
    return dynamic_cast<node*>(this->getElementByName(name,"node"));
}
