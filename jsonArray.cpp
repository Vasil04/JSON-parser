#include "jsonArray.h"

jsonArray::jsonArray(){
     
}

void jsonArray::parseData(string& jsonTXT, const string key, size_t& position){
    size_t counter = 0;
    while(jsonTXT[position] != ']'){
        if (jsonTXT[position] == '"'){

            position ++;
            size_t keyStart = position;
            
            while (position < jsonTXT.length() && jsonTXT[position] != '\"') {
                position++;
            }

            string keyLocal = jsonTXT.substr(keyStart, position - keyStart);
            position++;

            while(jsonTXT[position] != '"') position++;
            position++;
            skipWhiteSpaces(jsonTXT, position);

            simplePairs.parseData(jsonTXT, keyLocal, position);
        
            
        }
        else if(jsonTXT[position] == '{'){
            position ++;
            jsonObject.parseData(jsonTXT, std::to_string(counter), position);
            counter++;
        }
        else {
            position ++;
        }
    }

    allMembers[key] = jsonObject.getObjects();
    jsonObject.clear();
}

void jsonArray::printAllData(){
    // cout << this->key <<":"<< endl;
    simplePairs.printAllPairs();
    for (const auto& pair : allMembers)
    {
        cout << "Master key: " << pair.first <<endl;
        for(const auto& deeperPair : allMembers[pair.first]){
            cout << "Key: " << deeperPair.first << endl;
            for(const auto& deepestPair : allMembers[pair.first][deeperPair.first]){
                cout << "Key: " << deepestPair.first << ", Value: " << deepestPair.second <<endl;
            }
        }
    }
}
