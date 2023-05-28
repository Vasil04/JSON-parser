#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
// #include "Parser.hpp"
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

    map<string, map<string, string>> getObjects ();

    map<string, string> getObject (const string key);

    map<string, string> getObjectByPath (const string path);

    string getElementValue (const string masterKey, const string key);

    bool checkIfObjectExists (const string key);

    void searchByKey (string key);

    bool containsElement (const string path);

    void setElement (const string masterKey, const string key, const string newValue);
    void setElement (const string masterKey, map <string, string> Map);

    void saveChanges(string& jsontxt);
    void saveChangesForArray(string& jsontxt);

    void deleteWholeObject(const string name);

    void deleteElement(const string firstKey, const string secondKey);
    void deleteElement(const string path);

    void clear();

    public:
    // jsonObject();

    // jsonObject(const jsonObject& other) = delete;
    // jsonObject(jsonObject&& other) = delete;

    // jsonObject& operator=(const jsonObject& other) = delete;
    // jsonObject& operator=(jsonObject&& other) = delete;
};
#endif