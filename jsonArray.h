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

    std::vector <string> keys;
    map<string, map<string, string>> simpleElements;

    jsonObject jsonObjectInstance;
    // map<string, map<string, string>> allSimplePairs;
    // size_t spCounter = 0;
    // map<string, map<string, map<string, string>>> allMembers;

    // size_t joCounter = 0;
    map<string, map<string, std::vector<jsonObject>>> allMembers;
    
    public:
    
    void parseData(string& jsonTXT, const string key, size_t& position) override;
    void printAllData();
    void searchByKey (string key);
    bool containsElement (const string path);

    void setElement (const string firstKey, const string masterKey, const string secondKey, const string newValue);
    void setElement (const string firstKey, const string secondKey, const string newValue);
    void setElement(const string path, map<string, string> element);
    
    map<string, string> getElement (const string path);
    void addObject (const string arrayMasterKey, map<string, string> object);
    bool checkIfArrayExists(const string key);

    void deleteWholeArray(const string name);
    void deleteElement(const string firstKey, const string secondKey, const string thirdKey);
    void deleteElement(const string path);
    void deleteObject(const string firstKey, const string secondKey);

    void clear();

    void saveChanges(string& jsontxt);

    public:
    jsonArray();

    jsonArray(const jsonArray& other) = delete;
    jsonArray(jsonArray&& other) = delete;

    jsonArray& operator=(const jsonArray& other) = delete;
    jsonArray& operator=(jsonArray&& other) = delete;
};
#endif