#include "KVPairs.h"


    void KVPairs::addPairs (string key, string value){
        simplePairs[key] = value;
    }

    void KVPairs::printPair (string key){
        cout << simplePairs[key] << endl;
    }

    void KVPairs::printAllPairs(){
        for (const auto& pair : simplePairs)
        {
            cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl; 
        }
        
    }

    map<string, string> KVPairs::getSimplePairs () {
        return simplePairs;
    }

    void KVPairs::parseData(string& jsonTXT, const string key,size_t& position){

        size_t valueStart = position;
        while (position < jsonTXT.length() && jsonTXT[position] != '\"') {
                position++;
        }
        std::string value = jsonTXT.substr(valueStart, position - valueStart);
        // cout << valueStart << " " << position<< endl;
        position++;
        addPairs(key, value);
    }

    KVPairs::KVPairs(){
        
    }

    KVPairs::KVPairs(string key, string value){
        addPairs(key, value);
    }

