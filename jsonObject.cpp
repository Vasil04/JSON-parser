#include "jsonObject.h"

    // jsonObject::jsonObject(){
      
    // }

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
        simplePairs.clear();
    }

    void jsonObject::printAllData(){
        for (const auto& pair : allObjects)
        {
            cout << "Master key: " << pair.first <<endl;
            for(const auto& deeperPair : allObjects[pair.first]){
                cout << "Key: " << deeperPair.first << ", Value: " << deeperPair.second <<endl;
                // cout << "hello";
            }
        }
        cout << endl;
    }

    map<string, map<string, string>> jsonObject::getObjects (){
        return allObjects;
    }

    map<string, string> jsonObject::getObject (const string key){
        return allObjects[key];
    }

    map<string, string> jsonObject::getObjectByPath (const string path){
        string firstPart;
        string secondPart;

        size_t position = 0;
        while (position < path.length() && path[position] != '/') {
                position++;
        }
        
        firstPart = path.substr(0, position);
        // cout << firstKey << "hello" << endl;
        position ++;
        size_t start = position;
        while (position < path.length() && path[position] != '/') {
                position++;
        }
        secondPart = path.substr(start, position - start);

        map <string, string> element;
        element[secondPart] = allObjects[firstPart][secondPart];
        return element;
    }

    void jsonObject::searchByKey (string key){
        for(const auto& pair : allObjects)
        {
            if(startsWith (pair.first, key)) cout << pair.first << endl;
            
            for(const auto& deeperPair : allObjects[pair.first]){
                if (startsWith(deeperPair.first, key))
                {
                    cout << deeperPair.second << endl;
                }
                
            }
        }
    }

    void jsonObject::clear(){
        simplePairs.clear();
        allObjects.clear();
        key = " ";
    }

    void jsonObject::setElement (const string masterKey, const string key, const string newValue){
        allObjects[masterKey][key] = newValue;
    }

    void jsonObject::setElement (const string masterKey, map <string, string> Map){
        allObjects[masterKey][Map.begin()->first] = Map[Map.begin()->first];
    }
    string jsonObject::getElementValue (const string masterKey, const string key){
        return allObjects[masterKey][key];
    }
    bool jsonObject::checkIfObjectExists(const string key){
        for(const auto& pair : allObjects){
            if(pair.first == key){
                return true;
            }
        }
        return false;
    }

    void jsonObject::deleteWholeObject(const string name){
        allObjects.erase(name);
    }

    void jsonObject::deleteElement(const string firstKey, const string secondKey){
        allObjects[firstKey].erase(secondKey);
    }

    void jsonObject::deleteElement(const string path){
        string firstPart;
        string secondPart;

        size_t position = 0;
        while (position < path.length() && path[position] != '/') {
                position++;
        }
        
        firstPart = path.substr(0, position);
        // cout << firstKey << "hello" << endl;
        position ++;
        size_t start = position;
        while (position < path.length() && path[position] != '/') {
                position++;
        }
        secondPart = path.substr(start, position - start);
        allObjects[firstPart].erase(secondPart);
    }
   
    bool jsonObject::containsElement (const string path) {
        
        string firstKey;
        string secondKey;
        size_t position = 0;
        
        while (position < path.length() && path[position] != '/') {
                position++;
        }
        firstKey = path.substr(0, position);
        position ++;

        if (position < path.length())
        {
            size_t start = position;
            while (position < path.length() && path[position] != '/') {
                    position++;
            }
            secondKey = path.substr(start, position - start);
            for(const auto& pair : allObjects)
            {
                if(pair.first == firstKey){
                    for(const auto& deeperPair : allObjects[pair.first]){
                        if (deeperPair.first == secondKey)
                        {
                            return true;
                        }
                        
                    }
                    return false;
                }
            }
        }
        return false;
    }

    void jsonObject::saveChanges(string& jsontxt){
        for (const auto& pair : allObjects)
        {
            jsontxt += '"' + pair.first + '"' + ':';
            jsontxt += "{";
            for(const auto& deeperPair : allObjects[pair.first]){
                jsontxt += '"' + deeperPair.first + '"' + ':' + '"' + deeperPair.second + '"' + ',' + ' ';                             
            }
            jsontxt[jsontxt.rfind(',')] = ' '; 
            jsontxt += "},";
        }
    }

    void jsonObject::saveChangesForArray(string& jsontxt){
        for (const auto& pair : allObjects)
        {
            for(const auto& deeperPair : allObjects[pair.first]){
                jsontxt += '"' + deeperPair.first + '"' + ':' + '"' + deeperPair.second + '"' + ',' + ' ';                             
            }
            
        }
    }