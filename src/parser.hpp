#ifndef parserH
#define parserH
#include <vector>
#include "networkElement.hpp"
#include "router.hpp"
#include "node.hpp"

class parser{
    vector<networkElement*> networkObjects;
public:
    void parseFile(char* fileName);
    networkElement* getElementByName(string name,string type = "any");
    node* getNodeByName(string name);
    router* getRouterByName(string name);
    router* getRouterByIp(ipv4* ip);
    vector<networkElement*> getNetworkElements(){return this->networkObjects;}
    vector<node*> getNodes(void);
    vector<router*> getRouters(void);
    void tuneNetwork();
};
#endif
