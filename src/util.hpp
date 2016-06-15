#ifndef utilH
#define utilH
#include <string>
#include <vector>
using namespace std;

string tolowercase(string s);
vector<string> split(string str, char delimiter);
unsigned int ipv4AsBits(string ip);
string ipv4AsBitsString(unsigned int ip);
string ipv4AsBitsString(string ip);
string ipv4AsHumanReadable(unsigned int ip);
unsigned int getNetworkFromIp(unsigned int ip);
bool areSameNetwork(unsigned int ip1,unsigned int ip2);
bool fileExists(const std::string& name);
istream& safeGetline(std::istream& is, std::string& t);
#endif
