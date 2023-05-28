#include "KVPairs.h"


    void KVPairs::addPairs (string key, string value){
        simplePairs[key] = value;
        bool doesExist = false;
        for (size_t i = 0; i < keys.size(); i++)
        {
            if (keys[i] == key)
            {
                doesExist = true;
            }
            
        }
        if (!doesExist)
        {
            keys.push_back(key);
        }        
        
    }

    void KVPairs::printPair (string key){
        // for(int i = 0; i < keys.size(); i++){
        //     if (key == keys[i])
        //     {
                cout << simplePairs[key] << endl;
        //         break;
        //     }
        // }
    }

    bool KVPairs::containsElement(const string key){
        for (int i = 0; i < keys.size(); i++)
        {
            if(keys[i] == key){
                return true;
            }
        }
        return false;
    }

    void KVPairs::printAllPairs (){
        cout << endl;
        for (const auto& pair : simplePairs)
        {
            cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl; 
        }
        cout << endl;
    }

    void KVPairs::searchByKey (string key){
        for (int i = 0; i < keys.size(); i++)
        {
            if(startsWith(keys[i], key)){
                printPair(keys[i]);
            }
        }
    }

    string KVPairs::getElementAt(const string path){
        return simplePairs[path];
    }

    void KVPairs::deleteElement (const string key){
        simplePairs.erase(key);
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
        keys.push_back(key);
    }

    void KVPairs::clear(){
        simplePairs.clear();
        keys.clear();
    }

    void KVPairs::saveChanges(string& jsontxt){
        for (const auto& pair : simplePairs)
        {
            jsontxt += '"' + pair.first + '"' + ':' + '"' + pair.second + '"' + ',' + ' ';
        }
    }

