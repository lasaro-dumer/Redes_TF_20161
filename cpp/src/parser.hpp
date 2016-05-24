#ifndef parserH
#define parserH
#include <vector>
#include "networkElement.hpp"
#include "router.hpp"
#include "node.hpp"

class parser{
    //vector<networkElement> networkObjects;
    vector<node> netNodes;
    vector<router> netRouters;
public:
    void parseFile(char* fileName);
    vector<node> getNodes(void){return this->netNodes;}
    vector<router> getRouters(void){return this->netRouters;}
};
#endif
