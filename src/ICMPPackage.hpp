#ifndef ICMPPackageH
#define ICMPPackageH
#include "ipv4.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cmath>

class ICMPPackage {
private:
public:
    ipv4* src_IP;
    ipv4* srcHop_IP;
    ipv4* dst_IP;
    ipv4* dstHop_IP;
    string srcHop_MAC,srcHop_Name,dstHop_MAC,dstHop_Name;
    string message,type;
    bool moreFragments;
    int TTL, offset;
    //ICMPPackage(src_IP,srcHop_IP,srcHop_MAC,srcHop_Name,dst_IP,dstHop_IP,dstHop_MAC,dstHop_Name,message,type,ttl)
    ICMPPackage(ipv4* src,ipv4* srcHpI,string srcM,string srcN,ipv4* dst,ipv4* dstHpI,string dstM,string dstN,string m,string t,int _ttl)
                :src_IP(src),srcHop_IP(srcHpI),srcHop_MAC(srcM),srcHop_Name(srcN)
                ,dst_IP(dst),dstHop_IP(dstHpI),dstHop_MAC(dstM),dstHop_Name(dstN)
                ,message(m),type(t),TTL(_ttl){
                offset = 0;
                moreFragments = false;
                }

    void updateDataLinkInfo(string srcHopName,string srcHopMAC,string dstHopName,string dstHopMAC);
    string toString();

    static ICMPPackage echoRequest(ipv4* srcIP,ipv4* dstIP,string m, int _ttl = 8){
        ICMPPackage request(srcIP,nullptr,"","",dstIP,nullptr,"","",m,"request",_ttl);
        return request;
    }

    static ICMPPackage echoReply(ipv4* srcIP,ipv4* dstIP,string m, int _ttl = 8){
        ICMPPackage reply(srcIP,nullptr,"","",dstIP,nullptr,"","",m,"reply",_ttl);
        return reply;
    }

    static bool compare(ICMPPackage i,ICMPPackage j){
        return i.offset < j.offset;
    }

    static ICMPPackage remountMessage(vector<ICMPPackage> packages){
        stringstream ss;
        int npackages = packages.size();
        // using function as comp
        std::sort(packages.begin(), packages.end(), ICMPPackage::compare);
        for(int i =0;i<npackages;i++){
            ICMPPackage* auxpackage = &packages[i];
            ss << auxpackage->message;
        }
        ICMPPackage ping(packages[0].src_IP,packages[0].srcHop_IP,packages[0].srcHop_MAC,packages[0].srcHop_Name,packages[0].dst_IP,packages[0].dstHop_IP,packages[0].dstHop_MAC,packages[0].dstHop_Name,ss.str(),packages[0].type,packages[0].TTL);
        return ping;
    }

    static vector<ICMPPackage> sliceMessage(ICMPPackage package,int maxMTU){
        vector<ICMPPackage> packages;

        int message_s = package.message.size();
        int npackages = ceil((message_s*1.0)/(maxMTU*1.0));
        for(int i=0;i<npackages;i++){
            int noffset = i*maxMTU;
            string nmessage = package.message.substr(noffset,maxMTU);
            ICMPPackage ping(package.src_IP,package.srcHop_IP,package.srcHop_MAC,package.srcHop_Name,package.dst_IP,package.dstHop_IP,package.dstHop_MAC,package.dstHop_Name,nmessage,package.type,package.TTL);
            noffset += package.offset;
            ping.offset = noffset;
            ping.moreFragments = ((i+1)!=npackages) || package.moreFragments;
            packages.push_back(ping);
        }
        #ifdef DEBUG
        std::cout << "packages="<<packages.size() << std::endl;
        vector<ICMPPackage>::iterator ipkg;
        for (ipkg = packages.begin(); ipkg != packages.end(); ++ipkg) {
            std::cout << "package[]="<<(*ipkg).toString() << std::endl;
        }
        #endif
        return packages;
    }

    ~ICMPPackage(){
    }
};
#endif
