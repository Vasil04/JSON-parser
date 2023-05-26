#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include "KVPairs.h"
#include "Controller.h"
#include "jsonObject.h"
#include "jsonArray.h"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::ofstream, std::endl;
using namespace MyController;

int main(){

    string jsonTXT;

    //to be put under "open"
    ifstream file("JSONTXT.json");

    if (!file.is_open()){
        cout << "Error opening the file";
        return -1;
    }
    //end of open

    while (!file.eof()){
        getline(file, jsonTXT);
    }

    //to be put under close:
    file.close();

    //valdiation of the text;
    if(!validate(jsonTXT)){
        return -1;
    }

    //save as, and save will be the same but instead of some name given by a string it will be the default file name
    if (false)
    {
        ofstream outputFile("some name");
        outputFile << jsonTXT;
    }
    
    // some cout to be put here that shows all the features of the app:
    //....

    //example exit function, to be changed later
    if (false){
        return 0;
    }


    
    KVPairs tester;
    jsonObject jsonObject;
    jsonArray jsonArray;

    parseData(jsonTXT, tester, jsonObject, jsonArray);
    // tester.printAllPairs();
    // jsonObject.printAllData();
    // jsonArray.printAllData();

    searchKey("name", tester, jsonObject, jsonArray);
    // tester.addPairs("secondKey", "secondValue");

    // tester.printPair("firstKey");
    
    return 0;
    
}