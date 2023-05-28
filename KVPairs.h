#ifndef KVPAIRS_H
#define KVPAIRS_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include <vector>
#include "Parser.hpp"


class KVPairs : public Parser{

    private:
        map<string, string> simplePairs;
        std::vector<string> keys;

    public:

        void addPairs (string key, string value);

        void printPair (string key);
        
        void searchByKey (string key);

        bool containsElement(const string key);

        void printAllPairs ();

        map<string, string> getSimplePairs ();

        void parseData(string& jsonTXT, const string key, size_t& position) override;

        void deleteElement (const string key);

        string getElementAt(const string path);

        void clear();
        
        void saveChanges(string& jsontxt);

};
#endif