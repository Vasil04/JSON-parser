#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include "KVPairs.h"
#include "Controller.h"
#include "jsonObject.h"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;
using namespace MyController;

void someFunction(string& json, KVPairs& pairs, jsonObject& jsonObject){
    size_t position = 0;

    // cout << json.length() << endl;
    while (position < json.length())
    {
        while(json[position] != '"' && position < json.length()) {
            position++;
        }
        position++;

        size_t keyStart = position;

        if (!(position < json.length()))
        {
            break;
        }
        
        while (position < json.length() && json[position] != '\"') {
            position++;
        }

        std::string key = json.substr(keyStart, position - keyStart);
        position++;

        if (!(position < json.length()))
        {
            break;
        }
        while(json[position] != ':' && position < json.length()) position++;
        position++;

        if (!(position < json.length()))
        {
            break;
        }

        pairs.skipWhiteSpaces(json, position);
        if (json[position] == '"')
        {
            position++;
            pairs.parseData(json, key, position);
            
        }
        else if (json[position] == '{'){
            // while(json[position] != '}' && position < json.length()) position++;
            position++;
            jsonObject.skipWhiteSpaces(json, position);
            jsonObject.parseData(json, key, position);
        }
        else if (json[position] == '['){
            while(json[position] != ']' && position < json.length()) position++;
            position++;
        }
        
    }
}
int main(){

    string jsonTXT;

    // getline(cin, jsonTXT);

    ifstream file("JSONTXT.json");

    if (!file.is_open()){
        cout << "Error opening the file";
        return -1;
    }

    while (!file.eof()){
        getline(file, jsonTXT);
    }

    file.close();

    if(!MyController::validate(jsonTXT)){
        return -1;
    }

    KVPairs tester;
    jsonObject jsonObject;

    someFunction(jsonTXT, tester, jsonObject);
    tester.printAllPairs();
    jsonObject.printAllData();
    // tester.addPairs("secondKey", "secondValue");

    // tester.printPair("firstKey");
    
    return 0;
    
}