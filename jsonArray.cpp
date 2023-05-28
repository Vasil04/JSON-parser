#include "jsonArray.h"

jsonArray::jsonArray(){
     
}

void jsonArray::parseData(string& jsonTXT, const string key, size_t& position){
    size_t counter = 0;
    size_t valueStart;
    string value;

    while(jsonTXT[position] != ']'){
        if(jsonTXT[position] == '{'){
            position ++;
            jsonObjectInstance.parseData(jsonTXT, std::to_string(counter), position);
            allMembers[key][std::to_string(counter)].push_back(jsonObjectInstance);
            jsonObjectInstance.clear();
            counter++;
            
        }
        else if (jsonTXT[position] != ',' && jsonTXT[position] != ' '){
            skipWhiteSpaces(jsonTXT, position);
            valueStart = position;
            
            while (position < jsonTXT.length() && jsonTXT[position] != ',' && jsonTXT[position] != '}' && jsonTXT[position] != ' ' && jsonTXT[position] != ']') {
                position++;
            }

            value = jsonTXT.substr(valueStart, position - valueStart);
            position++;

            if(position >= jsonTXT.length()) break;
            skipWhiteSpaces(jsonTXT, position);

            simpleElements[key][std::to_string(counter)] = value;
            counter ++;
        }
        else {
            position ++;
        }
    }
    keys.push_back(key);
    // cout << endl << "/////////////////////";
    // jsonObjectInstance.printAllData();
    // cout << endl << "/////////////////////" << endl;
    // jsonObjectInstance.clear();
}

void jsonArray::printAllData(){
    // cout << this->key <<":"<< endl;
    // simplePairs.printAllPairs();
    // for (const auto& pair : allMembers)
    // {
    //     cout << "Master key: " << pair.first <<endl;
    //     for(const auto& deeperPair : allMembers[pair.first]){
    //         cout << "Key: " << deeperPair.first << endl;
    //         for(const auto& deepestPair : allMembers[pair.first][deeperPair.first]){
    //             cout << "Key: " << deepestPair.first << ", Value: " << deepestPair.second <<endl;
    //         }
    //     }
    // }
    //----------------------------------
    // for (size_t i = 0; i < simpleElements.size(); i++)
    // {
    //     cout << simpleElements[i];
    // }
    
    for (size_t i = 0; i < keys.size(); i++)
    {
        cout << keys[i] << ":" << endl;
        for (const auto& pair : simpleElements[keys[i]])
        {
            cout << pair.second<<endl;
        }

        for( auto&pair : allMembers[keys[i]]){
            // allMembers[keys[i]][pair.first][0].printAllData();
            pair.second[0].printAllData();
        }  

    }
    

    // for(const auto&pair : allMembers){
    //     cout << "Master key: " << pair.first <<endl;
    //     for(const auto&deeperPair : allMembers[pair.first]){
    //             allMembers[pair.first][deeperPair.first][0].printAllData();
    //     }     
    // }
}

//should probably adjust the logic for when the key is a master key
void jsonArray::searchByKey (string key){
    // for(const auto&pair : allSimplePairs){
    //     for (int i = 0; i < allSimplePairs[pair.first].size(); i++)
    //     {
    //         allSimplePairs[pair.first][i].searchByKey(key);
    //     }       
    // }

    // for (size_t i = 0; i < simpleElements.size(); i++)
    // {
    //     if(startsWith(simpleElements[i], key)){

    //     }
    // }
    
    for(const auto&pair : allMembers){
        for(auto&deeperPair : allMembers[pair.first])
            deeperPair.second[0].searchByKey(key);    
    }

}

void jsonArray::setElement (const string firstKey, const string masterKey, const string secondKey, const string newValue){
    allMembers[firstKey][masterKey][0].setElement(masterKey, secondKey, newValue);
}

void jsonArray::setElement(const string path, map<string, string> element){
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

    allMembers[firstPart][secondPart][0].setElement(secondPart, element.begin()->first , element[element.begin()->first]);
}
void jsonArray::setElement (const string firstKey, const string secondKey, const string newValue){
    string firstPart;
    string secondPart;

    size_t position = 0;
    while (position < firstKey.length() && firstKey[position] != '/') {
            position++;
    }
    
    firstPart = firstKey.substr(0, position);
    // cout << firstKey << "hello" << endl;
    position ++;
    size_t start = position;
    while (position < firstKey.length() && firstKey[position] != '/') {
            position++;
    }
    secondPart = firstKey.substr(start, position - start);

    allMembers[firstPart][secondPart][0].setElement(secondPart, secondKey, newValue);
}

map<string, string> jsonArray::getElement (const string path){
    string firstPart;
    string secondPart;
    string thirdPart;
    map <string, string> Map;
    size_t position = 0;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    
    firstPart = path.substr(0, position);

    position ++;
    size_t start = position;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    secondPart = path.substr(start, position - start);
    position ++;

    start = position;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    thirdPart = path.substr(start, position - start);

    Map[thirdPart] = allMembers[firstPart][secondPart][0].getElementValue(secondPart, thirdPart);
    return Map;
}
void jsonArray::addObject(const string arrayMasterKey, map<string, string> object){
    jsonObject jsonObjectInstance;
    int number = 0;
    for(const auto& pair : allMembers[arrayMasterKey]){
        if (number < std::stoi(pair.first))
        {
            number = std::stoi(pair.first);
        }
    }
    number ++;
    
    for(const auto& pair : object){
        jsonObjectInstance.setElement(std::to_string(number) ,pair.first, pair.second);
    }

    allMembers[arrayMasterKey][std::to_string(number)].push_back(jsonObjectInstance);
}
bool jsonArray::containsElement (const string path){
    string firstKey;
    string secondKey;
    string thirdKey = "";
    size_t position = 0;

    while (position < path.length() && path[position] != '/') {
            position++;
    }
    firstKey = path.substr(0, position);
    position ++;

    size_t start = position;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    secondKey = path.substr(start, position - start);

    position ++;

    start = position;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    if (position <= path.length()) 
    {   
       thirdKey = path.substr(start, position - start);
    }
    // for(const auto&pair : allSimplePairs){
    //     if(pair.first == firstKey){
    //         for (int i = 0; i < allSimplePairs[pair.first].size(); i++)
    //         {
    //             if(allSimplePairs[pair.first][i].containsElement(secondKey)){
    //                 return true;
    //             }
    //         }   
    //     }    
    // }
    if(thirdKey != ""){
        for (size_t i = 0; i < keys.size(); i++)
        {
            if (keys[i] == firstKey)
            {
                string concated = secondKey + "/" + thirdKey;
                if (allMembers[firstKey][secondKey][0].containsElement(concated))
                {
                    return true;
                }   
            }
        }
    }
    else {
        for (size_t i = 0; i < keys.size(); i++)
        {
            if (keys[i] == firstKey)
            {
                for(const auto&pair : allMembers[firstKey]){
                    if (pair.first == secondKey)
                    {
                        return true;
                    }
                    
                }
            }
        }
    }

    return false;
    
}

void jsonArray::deleteWholeArray(const string name){
    allMembers.erase(name);
    for (size_t i = 0; i < keys.size(); i++)
    {
        if (keys[i] == name)
        {
            keys.erase(keys.begin() + i);
        }
    }
}

void jsonArray::deleteElement(const string firstKey, const string secondKey, const string thirdKey){
    allMembers[firstKey][secondKey][0].deleteElement(secondKey, thirdKey);
}

void jsonArray::deleteObject(const string firstKey, const string secondKey){
    allMembers[firstKey].erase(secondKey);
}

void jsonArray::deleteElement(const string path){
    string firstPart;
    string secondPart;
    string thirdPart;

    size_t position = 0;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    
    firstPart = path.substr(0, position);

    position ++;
    size_t start = position;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    secondPart = path.substr(start, position - start);
    position ++;

    start = position;
    while (position < path.length() && path[position] != '/') {
            position++;
    }
    thirdPart = path.substr(start, position - start);

    deleteElement(firstPart, secondPart, thirdPart);
}

bool jsonArray::checkIfArrayExists(const string key){
    for (size_t i = 0; i < keys.size(); i++)
    {
        if (keys[i] == key)
        {
            return true;
        }
        
    }
    return false;
}
void jsonArray::clear(){
    keys.clear();
    simpleElements.clear();
    allMembers.clear();
    jsonObjectInstance.clear();
}

void jsonArray::saveChanges(string& jsontxt){
    for(const auto& pair : allMembers){
        jsontxt += '"' + pair.first + '"' + ':';
        jsontxt += "[";

        for (auto& deeperPair : allMembers[pair.first])
        {
            jsontxt += "{";

            deeperPair.second[0].saveChangesForArray(jsontxt);

            jsontxt[jsontxt.rfind(',')] = ' '; 
            jsontxt += "},";
        }
        jsontxt[jsontxt.rfind(',')] = ' '; 
        jsontxt += "],";
    }
}