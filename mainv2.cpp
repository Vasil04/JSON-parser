#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include <KVPairs.hpp>

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;

void skipWhiteSpaces(const string& jsonTXT, int& position){

    while(position < jsonTXT.length() && std::isspace(jsonTXT[position])) position++;

}

bool validate(const string& jsonTXT) {
    size_t position = 0;

}

// bool 

int main(){

    
    
}