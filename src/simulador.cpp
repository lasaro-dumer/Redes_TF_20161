#include <iostream>
#include <string>
#include "parser.hpp"
#include "ipv4.hpp"
#include "util.hpp"
using namespace std;

int main(int argc, char const *argv[]) {
    char* file=(char*)"";
    char* n1 = (char*)"";
    char* n2 = (char*)"";
    char* m = (char*)"";
    node* nN1;
    node* nN2;
    parser p;
    /* TEST IF IPS ARE ON SAME NETWORK
    if (argc>3){
        ipv4* mIp1=new ipv4((argv[2]));
        ipv4* mIp2=new ipv4((argv[3]));
        bool same = areSameNetwork(mIp1->getAsBits(),mIp2->getAsBits());
        std::cout << "same=" << same << std::endl;
    }//*/
    if(argc != 5){
        cout << "Invalid arguments" << endl;
        cout << "Input format is:" << endl;
        cout << "\tsimulador topology.txt sourceName destName message" << endl;
        return 1;
    }
    file = (char*)argv[1];
    n1 = (char*)argv[2];
    n2 = (char*)argv[3];
    m = (char*)argv[4];

    if(fileExists(string(file))){
        p.parseFile(file);
    }else{
        std::cout << "File doesn't exist" << std::endl;
        return 1;
    }
    nN1 = p.getNodeByName(n1);
    if(nN1 == nullptr){
        std::cout << "Source node ["<<n1<<"] not found" << std::endl;
        return 1;
    }
    nN2 = p.getNodeByName(n2);
    if(nN2 == nullptr){
        std::cout << "Destination node ["<<n2<<"] not found" << std::endl;
        return 1;
    }
    /* TO PRINT THE ARGUMENTS, COMMENT THIS LINE
    cout << "file="<<file << endl;
    cout << "n1="<<n1 << endl;
    cout << "n2="<<n2 << endl;
    cout << "m="<<m << endl;
    //*/

    /* TO PRINT DE PARSED ELEMENTS, COMMENT THIS LINE
    std::cout << "nodes"<< std::endl;
    vector<node*>::iterator i;
    vector<node*> ns = p.getNodes();
    for(i=ns.begin(); i != ns.end(); ++i){
        std::cout << (*i)->toString() << std::endl;
    }
    std::cout << "routers"<< std::endl;
    vector<router*>::iterator ii;
    vector<router*> rs = p.getRouters();
    for(ii=rs.begin(); ii != rs.end(); ++ii){
        std::cout << (*ii)->toString() << std::endl;
    }
    //*/
    /* TO TEST IPv4 UTILITIES
    //ipv4* mIp=new ipv4(string(n1));
    ipv4* mIp=new ipv4("129.129.129.129");
    std::cout << "mIp as is  ="<<mIp->getAsHumanReadable() << std::endl;
    std::cout << "mIp as bits="<<mIp->getAsBitsString() << std::endl;
    mIp=new ipv4("128.255.129.1");
    std::cout << "mIp as is  ="<<mIp->getAsHumanReadable() << std::endl;
    std::cout << "mIp as bits="<<mIp->getAsBitsString() << std::endl;
    mIp=new ipv4("127.129.2.255");
    std::cout << "mIp as is  ="<<mIp->getAsHumanReadable() << std::endl;
    std::cout << "mIp as bits="<<mIp->getAsBitsString() << std::endl;
    mIp=new ipv4("0.255.2.255");
    std::cout << "mIp as is  ="<<mIp->getAsHumanReadable() << std::endl;
    std::cout << "mIp as bits="<<mIp->getAsBitsString() << std::endl;
    //*/
    cout << "END" << endl;
    return 0;
}
