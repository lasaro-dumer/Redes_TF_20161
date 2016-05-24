#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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
