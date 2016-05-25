#include <iostream>
#include "parser.hpp"
#include "ipv4.hpp"
using namespace std;

int main(int argc, char const *argv[]) {
    char* file=(char*)"";
    char* n1 = (char*)"";
    char* n2 = (char*)"";
    char* m = (char*)"";
    parser p;
    for (int i = 0; i < argc; i++) {
        cout << "argv["<<i<<"]:"<<argv[i] << endl;
    }
    if (argc>1) {
        file = (char*)argv[1];
        //parse file
        p.parseFile(file);
    }
    if (argc>2) {
        n1 = (char*)argv[2];
    }
    if (argc>3) {
        n2 = (char*)argv[3];
    }
    if (argc>4) {
        m = (char*)argv[4];
    }
    /* TO PRINT THE ARGUMENTS, COMMENT THIS LINE
    cout << "file="<<file << endl;
    cout << "n1="<<n1 << endl;
    cout << "n2="<<n2 << endl;
    cout << "m="<<m << endl;
    //*/

    ///* TO PRINT DE PARSED ELEMENTS, COMMENT THIS LINE
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
