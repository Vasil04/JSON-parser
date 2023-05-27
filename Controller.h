#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <cctype>
#include <string>
#include <fstream>
#include "jsonArray.h"

namespace MyController{

    void skipWhitespace(const std::string& json, size_t& pos);
    bool validateValue(const std::string& json, size_t& pos);
    bool validateKey(const std::string& json, size_t& pos);
    bool validateObject(const std::string& json, size_t& pos);
    bool validateArray(const std::string& json, size_t& pos);
    bool validateValue(const std::string& json, size_t& pos);
    bool validate(const std::string& json);

    //Functions to be made:
    void print(KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);
    void searchKey(const string key, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays); //done
    void set(const string path, const string newValue, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);
    void create(const string path, const string value, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);
    void deleteElement(const string path);
    void move(const string from, const string to);

    void parseData(string& json, KVPairs& pairs, jsonObject& jsonObject, jsonArray& jsonArray);
}
#endif