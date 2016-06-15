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

string ipv4AsHumanReadable(unsigned int ip){
      stringstream ss;
      unsigned int p1 = ((255 << 24) & ip) >> 24;
      unsigned int p2 = ((255 << 16) & ip) >> 16;
      unsigned int p3 = ((255 << 8) & ip) >> 8;
      unsigned int p4 = (255) & ip;
      ss << p1 << "." << p2 << "." << p3 << "." << p4;
      return ss.str();
}

unsigned int getNetworkFromIp(unsigned int ip){
    //unsigned int classA = 0;
    unsigned int classB = 128<<24;
    unsigned int classC = 192<<24;
    unsigned int ipClass = ip & classC;
    if(ipClass == classC){
        return ip & ipv4AsBits("255.255.255.0");
    }else{
        ipClass = ip & classB;
        if(ipClass == classB){
            return ip & ipv4AsBits("255.255.0.0");
        }
        //must be classA
        return ip & ipv4AsBits("255.0.0.0");
    }
    return 0;
}

bool areSameNetwork(unsigned int ip1,unsigned int ip2){
    unsigned int network1 = getNetworkFromIp(ip1);
    unsigned int network2 = getNetworkFromIp(ip2);
    return (network1 == network2);
}
bool fileExists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

istream& safeGetline(std::istream& is, std::string& t)
{
    //Source: http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}
