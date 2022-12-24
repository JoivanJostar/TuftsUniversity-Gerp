
/*
* the implementation of stringProcessing functions
*/
#include <iostream>
#include "stringProcessing.h"
#include <string>
#include <sstream>
#include <iterator>
using namespace std;
std::string stripNonAlphaNum(std::string input) {
    string result;
    int beg = 0;
    int end = input.size();
    for (size_t i = 0; i < input.size(); ++i) {
        if (isalnum(input[i])) {
            beg = i;
            break;
        }
    }
    if (beg == (int) input.size())
        return "";
    for (int i =(int) input.size() - 1; i >=beg;--i) {
        if (isalnum(input[i])) {
            break;
        }
        end--;
    }

    return string{ input.begin() + beg, input.begin() + end };
}

//return a new lowercase string of the str
string toLowercase(std::string str) {
    string lowercase = str;
    for (size_t i = 0; i < str.length(); i++) {
        lowercase[i] = tolower(str[i]);
    }
    return lowercase;
}

vector<string> StringSplit(const char* s, size_t maxsize, char delim) {
	delim=0;
    istringstream iss(string(s, s + maxsize));
    vector<string> elems{istream_iterator<string>{iss},
    istream_iterator<string>{}};
    
 //   while (getline(iss, item, delim)) {
 //       if (!item.empty()) {
 //           elems.push_back(item);
 //       }
 //   }
    return elems;
}


