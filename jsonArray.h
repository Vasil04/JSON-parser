#ifndef JSONARRAY_H
#define JSONARRAY_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
// #include "Parser.hpp"
// #include "KVPairs.h"
#include "jsonObject.h"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;


class jsonArray : public Parser{
    
    private:
    // string key;
    KVPairs simplePairs;
    jsonObject jsonObject;
    map<string, map<string, map<string, string>>> allMembers;
    
    public:
    
    void parseData(string& jsonTXT, const string key, size_t& position) override;
    void printAllData();

    public:
    jsonArray();

    jsonArray(const jsonArray& other) = delete;
    jsonArray(jsonArray&& other) = delete;

    jsonArray& operator=(const jsonArray& other) = delete;
    jsonArray& operator=(jsonArray&& other) = delete;
};
#endif