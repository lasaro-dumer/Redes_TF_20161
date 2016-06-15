#include <iostream>
#include <string>
#include "parser.hpp"
#include "ipv4.hpp"
#include "util.hpp"
#include "ICMPPackage.hpp"
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
    #ifdef DEBUG
    std::cout << "DEBUG" << std::endl;
    #endif
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

    ICMPPackage ping = ICMPPackage::echoRequest(nN1->getIP(),nN2->getIP(),m,8);
    ping.srcHop_Name = nN1->getName();
    ping.srcHop_MAC = nN1->getMAC();
    ping.srcHop_IP = ping.src_IP;

    vector<ICMPPackage> requests;
    requests.push_back(ping);

    networkElement* current = nN1;

    bool printMac = true;
    while (current != nullptr) {
        if(requests.size() > 0){
            ipv4* dst_IP = requests[0].dst_IP;
            networkElement* next = nullptr;
            if(current->hasIP(dst_IP)){
                ICMPPackage request = ICMPPackage::remountMessage(requests);
                cout << current->getName() << " rbox " << current->getName() << " : Received "<< request.message <<";" << std::endl;
                if(request.type == "request"){
                    ICMPPackage reply = ICMPPackage::echoReply(request.dst_IP,request.src_IP,request.message,8);
                    reply.srcHop_Name = current->getName();
                    reply.srcHop_MAC = current->getMacToPort(dst_IP);
                    reply.srcHop_IP = reply.src_IP;
                    dst_IP = reply.dst_IP;
                    requests.clear();
                    requests.push_back(reply);
                }else{
                    break;
                }
            }
            ipv4 next_IP;
            next = current->getElementOrHopTo(dst_IP,next_IP);
            string mac = current->getMacFromArpTable(next_IP.getAsBits());
            if(mac == ""){
                mac = current->doArpRequest(next,&next_IP,printMac);
            }
            int mtu = current->getMtuToNextHop(dst_IP);
            mtu = 0;//TODO: remove this line after proper slice and remount methods
            vector<ICMPPackage> newRequests;
            vector<ICMPPackage>::iterator ireq;
            string currName = current->getName();
            string currMAC = current->getMacToPort(requests[0].srcHop_IP);
            string nextName = next->getName();
            string nextMAC = next->getMacToPort(&next_IP);
            for (ireq = requests.begin(); ireq < requests.end(); ++ireq) {
                (*ireq).updateDataLinkInfo(currName,currMAC,nextName,nextMAC);
                //This line print the ICMPPackage (be it request or reply)
                std::cout << (*ireq).toString() << std::endl;
                (*ireq).TTL--;
                vector<ICMPPackage> slices = ICMPPackage::sliceMessage(*ireq,mtu);
                vector<ICMPPackage>::iterator isls;
                for (isls = slices.begin(); isls < slices.end(); ++isls)
                    newRequests.push_back((*isls));
            }
            requests = newRequests;
            current = next;
        }else{
            current = nullptr;
        }
    }

    #ifdef DEBUG
    //PRINT DE PARSED ELEMENTS
    std::cout << "Parsed elements" << endl << std::endl;
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
    #endif
    return 0;
}
