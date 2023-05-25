#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include "Parser.h"
#include "KVPairs.h"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;


class jsonObject : public Parser{
    
    private:
    string key;
    KVPairs simplePairs;
    
    public:
    

    public:
    jsonObject();

    jsonObject(const jsonObject& other) = delete;
    jsonObject(jsonObject&& other) = delete;

    jsonObject& operator=(const jsonObject& other) = delete;
    jsonObject& operator=(jsonObject&& other) = delete;
};