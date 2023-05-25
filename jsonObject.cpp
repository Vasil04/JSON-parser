#include "jsonObject.h"

    jsonObject::jsonObject(){
      
    }

    void jsonObject::parseData(string& jsonTXT, const string key, size_t& position){
        while(jsonTXT[position] != '}'){
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
            else position++;
        }
        allObjects[key] = simplePairs.getSimplePairs();
    }

    void jsonObject::printAllData(){
        for (const auto& pair : allObjects)
        {
            cout << "Master key: " << pair.first <<endl;
            for(const auto& deeperPair : allObjects[pair.first]){
                cout << "Key: " << deeperPair.first << ", Value: " << deeperPair.second <<endl;
            }
        }
    }
