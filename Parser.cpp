#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;

class Parser {

public:
    virtual void parseData(string& jsonTXT);

    void skipWhiteSpaces(const string& jsonTXT, int& position) const{

        while(position < jsonTXT.length() && std::isspace(jsonTXT[position])) position++;

    }
    
    virtual ~Parser(){} 
};