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



public:

    JsonObject(string fileName){
      
    }

    JsonObject(const JsonObject&) = delete;
    JsonObject(JsonObject&&) = delete;

    JsonObject& operator=(const JsonObject&) = delete;
    JsonObject& operator=(JsonObject&&) = delete;

    ~JsonObject();
};