#include "Controller.h"

    void MyController::searchKey(const string key, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays){
        simplePairs.searchByKey(key);
        objects.searchByKey(key);
        arrays.searchByKey(key);
    }

    void MyController::set(const string path, const string newValue, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays){
        if(path.find('/') == std::string::npos){
            
            if (simplePairs.containsElement(path))
            {
                
                simplePairs.addPairs(path, newValue);
            }
        }
        else {
            if (objects.containsElement(path))
            {

                string firstKey;
                string secondKey;
                size_t position = 0;
                size_t valueStart = position;
                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                firstKey = path.substr(0, position);
                position ++;
                
                size_t start = position;
                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                secondKey = path.substr(start, position - start);

                objects.setElement(firstKey, secondKey, newValue);
            }
            else if (arrays.containsElement(path)){
                string firstKey;
                string secondKey;
                string thirdKey;

                size_t position = 0;

                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                firstKey = path.substr(0, position);
                position ++;
                
                size_t start = position;
                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                secondKey = path.substr(start, position - start);
                position ++;

                start = position;
                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                thirdKey = path.substr(start, position - start);
                arrays.setElement(firstKey, secondKey, thirdKey, newValue);
            }
            else {
                cout <<"Element not found" << endl;
            }
        }
    }

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
        return validateValue(json, pos);
    }

    bool MyController::validate(const std::string& json) {
        size_t pos = 0;

        if(json[pos] != '{') return false;

        pos++;
        return validateValue(json, pos);
    }

    void MyController::create(const string path, const string value, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays){
        // cout << path << "hello" << endl;
        if(path.find('/') == std::string::npos){
            simplePairs.addPairs(path, value);
        }
        else {
                string firstKey;
                string secondKey;
                string thirdKey = "";

                size_t position = 0;
                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                firstKey = path.substr(0, position);
                // cout << firstKey << "hello" << endl;
                position ++;
                if (arrays.checkIfArrayExists(firstKey))
                {
                    size_t start = position;
                    while (position < path.length() && path[position] != '/') {
                            position++;
                    }
                    secondKey = path.substr(start, position - start);
                    position ++;

                    if(arrays.containsElement(firstKey + "/" + secondKey)){
                        start = position;
                        
                        while (position < path.length() && path[position] != '/') {
                                position++;
                        }

                        if (position <= path.length())
                        {
                            thirdKey = path.substr(start, position - start);
                            arrays.setElement(firstKey, secondKey, thirdKey, value);
                        }

                        else {
                            cout << "Invalid input";
                        }
                        
                    }
                }
                
                else if (objects.checkIfObjectExists(firstKey)){
                    
                    size_t start = position;
                    while (position < path.length() && path[position] != '/') {
                            position++;
                    }
                    secondKey = path.substr(start, position - start);
                    objects.setElement(firstKey, secondKey, value);
                }
                else {
                    cout << "Element not found";
                }
                
        }
    }

    void MyController::move(const string from, const string to, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays){
        if(simplePairs.containsElement(from)){
            if (objects.checkIfObjectExists(to))
            {
                if (!objects.containsElement(to + "/" + from))
                {
                    objects.setElement(to, from, simplePairs.getElementAt(from));
                    simplePairs.deleteElement(from);
                }
            }
            else if (arrays.checkIfArrayExists(to.substr(0, to.find("/"))))
            {
                if (!arrays.containsElement(to + "/" + from))
                {
                    arrays.setElement(to, from, simplePairs.getElementAt(from));
                    simplePairs.deleteElement(from);
                }
            }
            else {
                cout << "Error when trying to move an element: an element with this key already exists within the desired location." << endl;
            }   
        }
        else if(from.find('/') == std::string::npos){
            if(objects.checkIfObjectExists(from)){
                if (to.find('/') != std::string::npos)
                {
                    cout << "You are trying to move the object inside another object/key-value pair which is a not supported feature" << endl;
                }
                else {
                    arrays.addObject(to, objects.getObject(from));
                    objects.deleteWholeObject(from);
                }
            }
        }
        else{
            if (objects.containsElement(from))
            {
                if (to == "origin")
                {
                    simplePairs.addPairs(objects.getObjectByPath(from).begin()->first, objects.getObjectByPath(from)[objects.getObjectByPath(from).begin()->first]);
                    objects.deleteElement(from);
                }
                else if (arrays.checkIfArrayExists(to.substr(0, to.find("/"))))
                {
                    if (!arrays.containsElement(to + "/" + from))
                    {
                        arrays.setElement(to, objects.getObjectByPath(from));
                        objects.deleteElement(from);
                    }
                }
                else if (objects.checkIfObjectExists(to)){
                    objects.setElement(to, from.substr(from.find("/") + 1, from.length()), objects.getElementValue( from.substr(0, from.find("/")), from.substr(from.find("/") + 1, from.length())));
                    objects.deleteElement(from);
                }
            }
            else if(arrays.containsElement(from)){
                if (to == "origin")
                {
                    simplePairs.addPairs(arrays.getElement(from).begin()->first, arrays.getElement(from)[arrays.getElement(from).begin()->first]);
                    arrays.deleteElement(from);
                }
                else if (arrays.checkIfArrayExists(to.substr(0, to.find("/"))))
                {
                    if (!arrays.containsElement(to + "/" + from))
                    {
                        arrays.setElement(to, arrays.getElement(from));
                        arrays.deleteElement(from);
                    }
                }
                else if (objects.checkIfObjectExists(to)){
                    objects.setElement(to, arrays.getElement(from));
                    arrays.deleteElement(from);
                }

                else cout << "Object not found" << endl;          
            }
            else{
                cout << "Object not found" << endl;
            }
        }

    }

    void MyController::deleteElement(const string path, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays){
        if(path.find('/') == std::string::npos){
            if (simplePairs.containsElement(path))
            {
                simplePairs.deleteElement(path);
            }
            else if (arrays.checkIfArrayExists(path)){
                arrays.deleteWholeArray(path);
            }
            else if (objects.checkIfObjectExists(path)){
                objects.deleteWholeObject(path);
            }
            else cout << "Error: Element not found." << endl;
        }
        else{
            if (objects.containsElement(path))
            {

                string firstKey;
                string secondKey;
                size_t position = 0;
                size_t valueStart = position;
                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                firstKey = path.substr(0, position);
                position ++;
                if(position <= path.length() && path[position]){
                    size_t start = position;
                    while (position < path.length() && path[position] != '/') {
                            position++;
                    }
                    secondKey = path.substr(start, position - start);

                    objects.deleteElement(firstKey, secondKey);
                }
                else {
                    objects.deleteWholeObject(firstKey);
                }
            }
            else if (arrays.containsElement(path)){
                string firstKey;
                string secondKey;
                string thirdKey;

                size_t position = 0;

                while (position < path.length() && path[position] != '/') {
                        position++;
                }
                firstKey = path.substr(0, position);
                position ++;
                if(position <= path.length() && path[position]){
                    size_t start = position;
                    while (position < path.length() && path[position] != '/') {
                            position++;
                    }
                    secondKey = path.substr(start, position - start);
                    position ++;
                    
                    if(position <= path.length() && path[position]){
                        start = position;
                        while (position < path.length() && path[position] != '/') {
                                position++;
                        }
                        thirdKey = path.substr(start, position - start);
                        arrays.deleteElement(firstKey, secondKey, thirdKey);
                    }
                    else {
                        arrays.deleteObject(firstKey, secondKey);
                    }
                }
                else {
                    arrays.deleteWholeArray(firstKey);
                }
            }
            else {
                cout <<"Element not found" << endl;
            }
        }
    }

    void MyController::parseData(string& json, KVPairs& pairs, jsonObject& jsonObject, jsonArray& jsonArray){
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
            // while(json[position] != ']' && position < json.length()) position++;
            position++;
            jsonArray.skipWhiteSpaces(json, position);
            jsonArray.parseData(json, key, position);
        }
        
    }
}

    void MyController::print(KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays){
        simplePairs.printAllPairs();
        objects.printAllData();
        arrays.printAllData();
    }

    void MyController::clear(KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays){
        simplePairs.clear();
        objects.clear();
        arrays.clear();
    }

    void MyController::separateWord(const string originWord, string& separatedWord, size_t& position){
        size_t wordNumber = position;
        while (originWord[position] == ' ' && position < originWord.length())
        {
            position++;
        }        

        size_t start = position;

        while(originWord[position] != ' ' && position < originWord.length()){
            position ++;
        }

        separatedWord = originWord.substr(start, position - start);

        if (wordNumber == 0)
        {
            std::transform(separatedWord.begin(), separatedWord.end(), separatedWord.begin(), ::tolower);
        }
        
    }

    void MyController::saveChanges(string& jsontxt, KVPairs& pairs, jsonObject& jsonObject, jsonArray& jsonArray){
        jsontxt += '{';
        pairs.saveChanges(jsontxt);
        jsonObject.saveChanges(jsontxt);
        jsonArray.saveChanges(jsontxt);
        jsontxt[jsontxt.rfind(',')] = ' ';
        jsontxt += '}';
    }