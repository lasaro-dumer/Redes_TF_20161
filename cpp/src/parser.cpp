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
    while(!myReadFile.eof()) // To get you all the lines.
    {
        getline(myReadFile,line); // Saves the line in line.
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
                        node n(name,mac,ip,mtu,gateway);
                        this->netNodes.push_back(n);
                        //std::cout << "n="<<n.toString() << std::endl;
                        break;
                    }
                case 2:
                    {
                        string name = s[0];
                        int nPorts = stoi(s[1],nullptr,10);
                        router r(name,nPorts);
                        int pn=0;
                        for (int i = 2; i < s.size(); i=i+3) {
                            string mac = s[i];
                            string ip = s[i+1];
                            int mtu = stoi(s[i+2],nullptr,10);
                            port* p = new port(mac,ip,mtu,pn);
                            r.addPort(p);
                            pn++;
                        }
                        this->netRouters.push_back(r);
                        //std::cout << "r="<<r.toString() << std::endl;
                        break;
                    }
                case 3:
                    {
        				string routerName = s[0];
        				string netDest =s[1];
        				string nextHop =s[2];
        				int portNumber=stoi(s[3],nullptr,10);
                        std::vector<router>::iterator iter, end;
                        for(iter = netRouters.begin(), end = netRouters.end() ; iter != end; ++iter) {
                            if (iter->getName() == routerName) {
                                port* p=iter->getPortByNumber(portNumber);
                                if(p->getPortNumber() > -1){
                                    te* entry = new te(netDest,nextHop,p);
                                    iter->addRouterTableEntry(entry);
                                }
                                //std::cout << r.getName() << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                default:
                    break;
            }
        }
    }
	myReadFile.close();
}
