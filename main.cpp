#include <iostream>
#include <string>
#include <cctype>
#include <map>

using std::string, std::cin, std::cout, std::map;

void skipWhiteSpaces(const string& jsonTXT, int& position);
map<string, string> parseJSON (const string& json);

class JsonObject{};

int main(){
    
    string jsonTXT;

    getline(cin, jsonTXT);

    map<string, string> jsonObject = parseJSON(jsonTXT);

    // map<string, JsonObject> George;
    // map<string, map<string, string>> John;

    cout << "Title: " << jsonObject["name"] << std::endl;
    cout << "City: " << jsonObject["city"] << std::endl;

    return 0;
}

void skipWhiteSpaces(const string& jsonTXT, int& position){

    while(position < jsonTXT.length() && std::isspace(jsonTXT[position])) position++;

}

map<string, string> parseJSON (const string& json){
    map<string, string> jsonObject;
    int position = 0;

    skipWhiteSpaces(json, position);

    if(json[position] != '{') {
        std::cout << "Invalid JSON format. Expected to start with '{'.";
        return jsonObject;
    }

    position ++;

    while (position < json.length())
    {
        skipWhiteSpaces(json, position);

        if (json[position] == '}')
        {
            position++;
            break;
        }

        if (json[position] != '\"') {
            std::cout << "Invalid JSON: Expected '\"' at position " << position << std::endl;
            return jsonObject;
        }

        position++;

        
        size_t keyStart = position;
        while (position < json.length() && json[position] != '\"') {
            position++;
        }

        //second quote of key
        if (json[position] != '\"') {
            std::cout << "Invalid JSON: Unterminated key string starting at position " << keyStart << std::endl;
            return jsonObject;
        }

        std::string key = json.substr(keyStart, position - keyStart);
        position++;

        skipWhiteSpaces(json, position);

        if (json[position] != ':') {
            std::cout << "Invalid JSON: Expected ':' at position " << position << std::endl;
            return jsonObject;
        }

        position++; 

        skipWhiteSpaces(json, position);

        //first quote of value
        if (json[position] != '\"') {
            std::cout << "Invalid JSON: Expected '\"' at position " << position << std::endl;
            return jsonObject;
        }

        position++; 

       
        size_t valueStart = position;
        while (position < json.length() && json[position] != '\"') {
            position++;
        }

        //second quote of value
        if (json[position] != '\"') {
            std::cout << "Invalid JSON: Unterminated value string starting at position " << valueStart << std::endl;
            return jsonObject;
        }

        std::string value = json.substr(valueStart, position - valueStart);

        position++;

        if (json[position] != ',')
        {
            skipWhiteSpaces(json, position);

            if (json[position] != '}')
            {
                std::cout << "Invalid JSON: Expected ',' at position " << position << std::endl;
                return jsonObject;
            }
        }

        position++;

        jsonObject[key] = value;
    }

    return jsonObject;

}