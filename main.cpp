#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include "KVPairs.h"
#include "Controller.h"
#include "jsonObject.h"
#include "jsonArray.h"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::ofstream, std::endl, std::getline;
using namespace MyController;

int main(){

    string jsonTXT;
    string userInput;
    string fileName;

    // cout << "Please choose one of the following commands: open - to open a file, help - to get a list of commands, exit - to exit the program" << endl;
    // getline(cin, userInput);

    // while (userInput != "exit")
    // {
    //     if(userInput == "help"){
    //         cout << "Open: type in open and click enter and afterwards input the file you would like to open." << endl << "Close: type in close to close the current file" << endl << "Save: type in save to save the changes on the current file" << endl << "Save as: type in save as to save the current file under your desired name" << endl << "Exit: type in exit to quit the program" << endl << "Print: type in print to have all the information from the file printed" << endl << "Search: type in search to get info about all the elements with this key" << endl << "Set: type in set to change the value of an element" << endl << "Create: type in create to create a new element" << endl << "Delete: type in delete to delete an element" << endl << "Move: type in move to move all elements" << endl;
    //     }

        
    // }
    

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
    // if (false){
    //     return 0;
    // }


    
    KVPairs tester;
    jsonObject jsonObject;
    jsonArray jsonArray;

    parseData(jsonTXT, tester, jsonObject, jsonArray);
    print(tester, jsonObject, jsonArray);

    // searchKey("name", tester, jsonObject, jsonArray);

    // set("offices/name", "works", tester, jsonObject, jsonArray);

    // cout << "///////////////////////////////////////////////";

    // print(tester, jsonObject, jsonArray);
    
    // tester.addPairs("secondKey", "secondValue");

    // tester.printPair("firstKey");
    
    return 0;
    
}