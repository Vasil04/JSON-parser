#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include "Parser.hpp"
#include "KVPairs.h"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;


class jsonObject : public Parser{
    
    private:
    string key;
    KVPairs simplePairs;
    map<string, map<string, string>> allObjects;
    
    public:
    
    void parseData(string& jsonTXT, const string key, size_t& position) override;
    void printAllData();

    public:
    jsonObject();

    jsonObject(const jsonObject& other) = delete;
    jsonObject(jsonObject&& other) = delete;

    jsonObject& operator=(const jsonObject& other) = delete;
    jsonObject& operator=(jsonObject&& other) = delete;
};
#endif