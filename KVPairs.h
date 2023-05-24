#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include "Parser.cpp"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;


class KVPairs : public Parser{

    private:
        map<string, string> simplePairs;

    public:

        void addPairs (string key, string value);

        void printPair (string key);

        map<string, string> getSimplePairs ();

        void parseData(string& jsonTXT) override;

    public:
        KVPairs();

        KVPairs(string key, string value);

        KVPairs(const KVPairs& other) = delete;
        KVPairs(KVPairs&& other) = delete;

        KVPairs& operator=(const KVPairs& other) = delete;
        KVPairs& operator=(KVPairs&& other) = delete;

};