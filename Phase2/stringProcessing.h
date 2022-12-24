/*
* some stringProcessing functions interface
*/

#ifndef __STRING_PROCESSING_H__
#define __STRING_PROCESSING_H__

#include <string>
#include <vector>
std::string stripNonAlphaNum(std::string input);
//return the lowercase of the string
std::string toLowercase(std::string str);
//split a string by delim character
//e.g "abc cds kkk" the delim is space character' ', 
//the split result is ["abc","cds","kkk" ]
std::vector<std::string> StringSplit(const char* s, size_t maxsize, char delim);
#endif