#include "KVPairs.h"


    void KVPairs::addPairs (string key, string value){
        simplePairs[key] = value;
    }

    void KVPairs::printPair (string key){
        cout << simplePairs[key] << endl;
    }

    map<string, string> KVPairs::getSimplePairs () {
        return simplePairs;
    }

    void KVPairs::parseData(string& jsonTXT){
        int position = 0;

        skipWhiteSpaces(jsonTXT, position);

        if(jsonTXT[position] != '{') {
            std::cout << "Invalid JSON format. Expected to start with '{'.";
            return;
        }

        position ++;

        while (position < jsonTXT.length())
        {
            skipWhiteSpaces(jsonTXT, position);

            if (jsonTXT[position] == '}')
            {
                position++;
                break;
            }

            if (jsonTXT[position] != '\"') {
                std::cout << "Invalid JSON: Expected '\"' at position " << position << std::endl;
                return;
            }

            position++;

            
            size_t keyStart = position;
            while (position < jsonTXT.length() && jsonTXT[position] != '\"') {
                position++;
            }

            //second quote of key
            if (jsonTXT[position] != '\"') {
                std::cout << "Invalid JSON: Unterminated key string starting at position " << keyStart << std::endl;
                return;
            }

            std::string key = jsonTXT.substr(keyStart, position - keyStart);
            position++;

            skipWhiteSpaces(jsonTXT, position);

            if (jsonTXT[position] != ':') {
                std::cout << "Invalid JSON: Expected ':' at position " << position << std::endl;
                return;
            }

            position++; 

            skipWhiteSpaces(jsonTXT, position);

            //first quote of value
            if (jsonTXT[position] != '\"') {
                std::cout << "Invalid JSON: Expected '\"' at position " << position << std::endl;
                return;
            }

            position++; 

        
            size_t valueStart = position;
            while (position < jsonTXT.length() && jsonTXT[position] != '\"') {
                position++;
            }

            //second quote of value
            if (jsonTXT[position] != '\"') {
                std::cout << "Invalid JSON: Unterminated value string starting at position " << valueStart << std::endl;
                return;
            }

            std::string value = jsonTXT.substr(valueStart, position - valueStart);

            position++;

            if (jsonTXT[position] != ',')
            {
                skipWhiteSpaces(jsonTXT, position);

                if (jsonTXT[position] != '}')
                {
                    std::cout << "Invalid JSON: Expected ',' at position " << position << std::endl;
                    return;
                }
            }

            position++;

            // simplePairs[key] = value;
            addPairs(key, value);
        }   

    // return jsonObject;
    }

    KVPairs::KVPairs(){
        
    }

    KVPairs::KVPairs(string key, string value){
        addPairs(key, value);
    }

