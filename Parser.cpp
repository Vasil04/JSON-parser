#include "Parser.hpp"

    void Parser::skipWhiteSpaces(const string& jsonTXT, size_t& position) {

        while(position < jsonTXT.length() && std::isspace(jsonTXT[position])) position++;

    }

    void Parser::parseData(string& jsonTXT, const string key, size_t& position){
        
    }

    Parser::~Parser(){

    }