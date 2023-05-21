#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;

class JsonObject{

private:
    string jsonTXT;
    

private:

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

    void extractText(string fileName){
        ifstream file(fileName);

        if (!file.is_open()){
            cout << "Error opening the file";
            return;
        }

        while (!file.eof()){
            getline(file, this->jsonTXT);
        }

        file.close();
    }


public:

    JsonObject(string fileName){
        extractText(fileName);
        parseJSON(jsonTXT);
    }

    JsonObject(const JsonObject&) = delete;
    JsonObject(JsonObject&&) = delete;

    JsonObject& operator=(const JsonObject&) = delete;
    JsonObject& operator=(JsonObject&&) = delete;

    ~JsonObject();
};