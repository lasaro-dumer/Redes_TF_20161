#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

string tolowercase(string s){
    int i=0;
    char c;
    while (s[i])
    {
        c=s[i];
        s[i]= (char)(tolower(c));
        i++;
    }
    return s;
}
vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;
	while(getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}
unsigned int ipv4AsBits(string ip){
    vector<string> s = split(ip,'.');
    unsigned int p1 = stoul(s[0],nullptr,10) << 24;
    unsigned int p2 = stoul(s[1],nullptr,10) << 16;
    unsigned int p3 = stoul(s[2],nullptr,10) << 8;
    unsigned int p4 = stoul(s[3],nullptr,10);
    return p1 ^ p2 ^ p3 ^ p4;
}
string ipv4AsBitsString(unsigned int ip){
    return bitset<32>(ip).to_string();
}
string ipv4AsBitsString(string ip){
    return ipv4AsBitsString(ipv4AsBits(ip));
}
bool fileExists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
