#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;
/**
     * @brief This class is inherited by all three other classes.
     * This class is inherited by all three other classes because it hold some functions that all other classes have or use. More to be added, currently there are several functions that are the same for two or more classes and they are to be moved here in the future.
*/
class Parser {

public:
    virtual void parseData(string& jsonTXT, const string key, size_t& position);

    void skipWhiteSpaces(const string& jsonTXT, size_t& position);

    /**
     * @brief checks if the provided string starts with the provided key
    */
    bool startsWith(const std::string &str, const std::string &prefix);
    
    virtual ~Parser();
};
#endif