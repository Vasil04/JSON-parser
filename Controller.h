#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <cctype>
#include <string>
#include <fstream>

namespace MyController{

    void skipWhitespace(const std::string& json, size_t& pos);
    bool validateValue(const std::string& json, size_t& pos);
    bool validateKey(const std::string& json, size_t& pos);
    bool validateObject(const std::string& json, size_t& pos);
    bool validateArray(const std::string& json, size_t& pos);
    bool validateValue(const std::string& json, size_t& pos);
    bool validate(const std::string& json);
}
#endif