#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;

class Parser {

public:
    virtual void parseData(string& jsonTXT, const string key, size_t& position);

    void skipWhiteSpaces(const string& jsonTXT, size_t& position);
    
    virtual ~Parser();
};
#endif