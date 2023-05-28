#ifndef KVPAIRS_H
#define KVPAIRS_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include <vector>
#include "Parser.hpp"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;


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
    public:
        // KVPairs();

        // KVPairs(string key, string value);

        // KVPairs(const KVPairs& other) = delete;
        // KVPairs(KVPairs&& other) = delete;

        // KVPairs& operator=(const KVPairs& other) = delete;
        // KVPairs& operator=(KVPairs&& other) = delete;

};
#endif