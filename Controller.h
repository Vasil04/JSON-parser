#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <algorithm>
#include "jsonArray.h"

/**
 * @brief This namespace holds the functions that the main file needs to execute the tasks.
 * Here are all of the functions that are used in the execution of the program, some of them are user related, and the rest are needed for running other functions.
*/
namespace MyController{
    /**
     * @brief skipps the empty spaces in a string
     * This function skipps the empty spaces in a string by being passed the string itself and the current position in the string. The current position changes inside the fucntion and since it's passed by a reference it also changes inside the fucntion where skipWhitespace is called. 
    */
    void skipWhitespace(const std::string& json, size_t& pos);

    /**
     * @brief This function checks the key(explained in the validateValue).
    */
    bool validateKey(const std::string& json, size_t& pos);

    /**
     * This is the function responsible for checking whether the value is valid or no when it is an object.
     * First it checks if the value begins with a curly bracket and if that is correct it calls validateValue to check the inside.
     * At last it checks if the object is closed properly
    */
    bool validateObject(const std::string& json, size_t& pos);

    /**
     * This is the function responsible for checking whether the value is valid or no when it is an array.
     * First it checks if the value begins with a square bracket and if that is correct it calls validateValue to check the inside.
     * At last it checks if the array is closed properly
    */
    bool validateArray(const std::string& json, size_t& pos);

    /**
     * This function is responsible for checking the keys and values of the elements (the values are checked through recursion) in the json file. Since the values can be plain text, arrays and objects the validateValue has a case for every one of those situations.
     * First the key is checked. It has to be surrounded by quotes and followed by ':'.
     * Then if the value is plain text it checks if it's surrounded by quotes and if it is not the last element before the file end, the value should be followed by a comma.
     * If the value is an object or an array it calls the corresponding functions;
    */
    bool validateValue(const std::string& json, size_t& pos);

    /**
     * This is the head validating function, it operates by calling sub-functions and returning the result from them;
    */
    bool validate(const std::string& json);

    /**
     * @brief this function prints all collected data by calling class specific functions
    */
    void print(KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);

    /**
     * @brief this function searches all elements starting with a keyword by calling class specific functions
     * All elements starting with the keyword are found and printed
    */
    void searchKey(const string key, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);

    /**
     * @brief This function checks if such element exist and changes it's value by calling class specific functions
    */
    void set(const string path, const string newValue, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);

    /**
     * @brief This function checks if the provided path leads to the inside of an existing element and if so creates the wanted element by calling class specific functions
    */
    void create(const string path, const string value, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);

    /**
     * @brief This function checks if such element exist and deletes it's value by calling class specific functions
    */
    void deleteElement(const string path, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);

    /**
     * @brief This function checks if such element exist and moves it's value(deletes it in one place and creates it in other) by calling class specific functions
    */
    void move(const string from, const string to, KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);

    /**
     * @brief This function separates user input into words so that other functions can use them separately
    */
    void separateWord(const string originWord, string& separatedWord, size_t& position);

    /**
     * @brief This function clears all json elements
    */
    void clear(KVPairs& simplePairs, jsonObject& objects, jsonArray& arrays);

    /**
     * @brief This function is used to extract the data and save it into the class objects created for this purpose (is called after validate)
    */
    void parseData(string& json, KVPairs& pairs, jsonObject& jsonObject, jsonArray& jsonArray);

    /**
     * @brief This function exports all changes into a string by calling class specific functions.
    */
    void saveChanges(string& jsontxt, KVPairs& pairs, jsonObject& jsonObject, jsonArray& jsonArray);
}
#endif