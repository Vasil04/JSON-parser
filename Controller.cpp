#include "Controller.h"



    void MyController::skipWhitespace(const std::string& json, size_t& pos) {
        while (pos < json.length() && std::isspace(json[pos])) {
            pos++;
        }
    }

    bool MyController::validateValue(const std::string& json, size_t& pos);
    bool MyController::validateKey(const std::string& json, size_t& pos){
        if (json[pos] == '"') {
            pos++; // Skip '\"'

            size_t valueStart = pos;
            while (pos < json.length() && json[pos] != '\"') {
                pos++;
            }

            if (json[pos] != '"') {
                std::cout << "Invalid JSON: Unterminated value string starting at position " << valueStart << std::endl;
                return false;
            }

            pos++; // Skip '\"'

            skipWhitespace(json, pos);
            if (json[pos] != ':') {
                std::cout << "Invalid JSON: Expected : at " << pos << std::endl;
                return false;
            }
            
            pos++;

            return true;
        }
        else {
            std::cout << "Invalid JSON: Unexpected character at position " << pos << std::endl;
            return false;
        }
    }

    bool MyController::validateObject(const std::string& json, size_t& pos) {
        // skipWhitespace(json, pos);

        // if (json[pos] != '{') {
        //     std::cout << "Invalid JSON: Expected '{' at position " << pos << std::endl;
        //     return false;
        // }//useless

        pos++; // Skip '{'

        skipWhitespace(json, pos);

        if (json[pos] == '}') {
            // pos++; // Skip '}'
            return true;
        }

        while (pos < json.length()) {

            // if(!validateKey(json, pos)) return false;

            if (!validateValue(json, pos)) {
                return false;
            }//validate key first or perhaps validate

            skipWhitespace(json, pos);

            // if (json[pos] == ',') {
            //     pos++; // Skip ','
            // }//useless most likely
            if (json[pos] == '}') {
                // pos++; // Skip '}'
                break;
            }
            else {
                std::cout << "Invalid JSON: Expected ',' or '}' at position " << pos << std::endl;
                return false;
            }
        }

        return true;
    }

    bool MyController::validateArray(const std::string& json, size_t& pos) {
        pos++; // Skip '['

        skipWhitespace(json, pos);

        if (json[pos] == ']') {
            // pos++; // Skip '}'
            return true;
        }
        
        while (pos < json.length()) {

            // if(!validateKey(json, pos)) return false;

            if (!validateValue(json, pos)) {
                return false;
            }//validate key first or perhaps validate

            skipWhitespace(json, pos);

            // if (json[pos] == ',') {
            //     pos++; // Skip ','
            // }//useless most likely
            if (json[pos] == ']') {
                // pos++; // Skip '}'
                break;
            }
            else {
                std::cout << "Invalid JSON: Expected ',' or ']' at position " << pos << std::endl;
                return false;
            }
        }

        return true;
    }

    bool MyController::validateValue(const std::string& json, size_t& pos) {

        skipWhitespace(json, pos);
        // if (pos == json.length() - 1) {
        //     std::cout << "test";
        //     return true;
        // }

        if (json[pos] == '{') {
            if(!validateObject(json, pos)) return false;

            if (json[++pos] != ',')
            {
                skipWhitespace(json, pos);
            
                if (json[pos] == '}' || json[pos] == ']') {
                    // pos++;
                    return true;
                }

                else if (json[pos] != '}' || json[pos != ']'])
                {
                    std::cout << "Invalid JSON: Expected ',' at position " << pos << std::endl;
                    return false;
                }
                
            }

            pos++;
            skipWhitespace(json, pos);        
        }
        else if (json[pos] == '[') {
            if(!validateArray(json, pos)) return false;
            
            if (json[++pos] != ',')
            {
                skipWhitespace(json, pos);
            
                if (json[pos] == '}' || json[pos] == ']') {
                    // pos++;
                    return true;
                }

                else if (json[pos] != '}' || json[pos != ']'])
                {
                    std::cout << "Invalid JSON: Expected ',' at position " << pos << std::endl;
                    return false;
                }
                
            }

            pos++;
            skipWhitespace(json, pos);  
        }

        else if (!validateKey(json, pos))
        {
            return false;
        }
        
        skipWhitespace(json, pos);

        if (json[pos] == '{') {
            if(!validateObject(json, pos)) return false;
        }
        else if (json[pos] == '[') {
            if(!validateArray(json, pos)) return false;
        }
        else if (json[pos] == '"') {
            pos++; // Skip '\"'

            size_t valueStart = pos;
            while (pos < json.length() && json[pos] != '\"') {
                pos++;
            }

            if (json[pos] != '"') {
                std::cout << "Invalid JSON: Unterminated value string starting at position " << valueStart << std::endl;
                return false;
            }

            // pos++; // Skip '\"'
        }

        else {
            std::cout << "Invalid JSON: Unexpected character at position " << pos<< std::endl;
            return false;
        }

        if (json[++pos] != ',')
        {
            // std::cout<<json[pos] << " " << pos << " ";
            // std::cout << "Currently at: " << json[pos] << " Number: " << pos << std::endl;
            skipWhitespace(json, pos);
            // std::cout << "Currently at: " << json[pos] << " Number: " << pos << std::endl;
            // std::cout << json[pos];
            if (json[pos] == '}') {
                // pos++;
                return true;
            }

            else if(json[pos] == ']' && pos < json.length()){
                return true;
            }

            else if (json[pos] != '}')
            {
                std::cout << "Invalid JSON: Expected ',' at position " << pos << std::endl;
                return false;
            }
            
        }

        // if (pos >= json.length() - 1) return true;
        
        pos++;
        validateValue(json, pos);
    }

    bool MyController::validate(const std::string& json) {
        size_t pos = 0;

        if(json[pos] != '{') return false;

        pos++;
        return validateValue(json, pos);
    }