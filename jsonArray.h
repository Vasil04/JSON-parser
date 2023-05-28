#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "jsonObject.h"


class jsonArray : public Parser{
    
    private:

    /**
     * @brief holds all areys' keys
    */
    std::vector <string> keys;

    /**
     * @brief This is a feature that is not currently in use
    */
    map<string, map<string, string>> simpleElements;

    jsonObject jsonObjectInstance;
    

    /**
     * @brief This holds all elements of all arrays
    */
    map<string, map<string, std::vector<jsonObject>>> allMembers;
    
    public:
    
    /**
     * @brief This function is called to extract array data into the array container
    */
    void parseData(string& jsonTXT, const string key, size_t& position) override;

    /**
     * @brief This function is called to print all array data
    */
    void printAllData();

    /**
     * @brief This function is used to find a specific array
    */
    void searchByKey (string key);

    /**
     * @brief This function is used to see if an array contains the wanted element
    */
    bool containsElement (const string path);

    /**
     * @brief This function sets an element by specific params
    */
    void setElement (const string firstKey, const string masterKey, const string secondKey, const string newValue);
    /**
     * @brief This function sets an element by different specific params
    */
    void setElement (const string firstKey, const string secondKey, const string newValue);
    /**
     * @brief This function sets an element by different specific params
    */
    void setElement(const string path, map<string, string> element);
    
    /**
     * @brief This function returns an element
    */
    map<string, string> getElement (const string path);
    void addObject (const string arrayMasterKey, map<string, string> object);
    bool checkIfArrayExists(const string key);

    void deleteWholeArray(const string name);
    void deleteElement(const string firstKey, const string secondKey, const string thirdKey);
    void deleteElement(const string path);
    void deleteObject(const string firstKey, const string secondKey);

    void clear();

    void saveChanges(string& jsontxt);
};
#endif