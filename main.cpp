#include <map>
#include "Controller.h"

using std::ofstream, std::getline;
using namespace MyController;

int main(){

    string jsonTXT;

    string userInput;

    string fileName;

    string firstWord;
    string secondWord;
    string thirdWord;

    size_t counter = 0;

    /**
     * @brief holds info on whether a file has been opened successfully or not.
    */
    bool openCalled = false;

    ifstream file;

    KVPairs tester;
    jsonObject jsonObject;
    jsonArray jsonArray;

    cout << "Please choose one of the following commands: open <filename> - to open a file, help - to get a list of commands, exit - to exit the program" << endl;
    getline(cin, userInput);
    separateWord(userInput, firstWord, counter);

    /**
     *@brief this is the loop that runs the program. 
    */
    while (firstWord != "exit")
    {
        if(firstWord == "help"){
            cout << "Open <filename>: type in open and the name of the file you would like to open." << endl << "Close: type in close to close the current file" << endl << "Save: type in save to save the changes on the current file" << endl << "Saveas: type in save as to save the current file under your desired name" << endl << "Exit: type in exit to quit the program" << endl << "Print: type in print to have all the information from the file printed" << endl << "Search <key>: type in search to get info about all the elements starting with this key" << endl << "Set <path> <string>: type in set to change the value of an element" << endl << "Create <path> <string>: type in create to create a new element" << endl << "Delete <path>: type in delete to delete an element" << endl << "Move <from> <to>: type in move to move all elements (info* - to move an element outside of an array or object use the keyword origin when inputing the <to> parameter)" << endl;
        }
        
        else if (firstWord == "open"){
            if (!openCalled)
            {            
                separateWord(userInput, fileName, counter);

                file.open(fileName);

                if (!file.is_open()){
                    cout << "Error opening the file" << endl;
                    // return -1;
                }
                else{
                    while (!file.eof()){
                        getline(file, jsonTXT);
                    }
                    if(!validate(jsonTXT)){
                        cout << "The file you tried to open does not follow the JSON syntax" << endl;
                    }
                    else {
                        openCalled = true;
                        parseData(jsonTXT, tester, jsonObject, jsonArray);
                        file.close();
                    }
                }
            }
            else {
                cout << "You have already opened a file" << endl;
            }
        }
        
        else if (firstWord == "close" && openCalled){
            if (openCalled)
            {
                openCalled = false;
                jsonTXT = " ";
                clear(tester, jsonObject, jsonArray);
                cout << fileName << " has been closed" << endl;
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if (firstWord == "print"){
            if (openCalled)
            {           
                print(tester, jsonObject, jsonArray);
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if (firstWord == "search"){
            if (openCalled)
            {
                separateWord(userInput, secondWord, counter);
                searchKey(secondWord, tester, jsonObject, jsonArray);
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if (firstWord == "set") {
            if (openCalled)
            {
                separateWord(userInput, secondWord, counter);
                separateWord(userInput, thirdWord, counter);
                set(secondWord, thirdWord, tester, jsonObject, jsonArray);
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if (firstWord == "create") {
            if (openCalled)
            {               
                separateWord(userInput, secondWord, counter);
                separateWord(userInput, thirdWord, counter);
                create(secondWord, thirdWord, tester, jsonObject, jsonArray);
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if(firstWord == "delete") {
            if (openCalled)
            {               
                separateWord(userInput, secondWord, counter);
                deleteElement(secondWord, tester, jsonObject, jsonArray);
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if(firstWord == "move") {
            if (openCalled)
            {               
                separateWord(userInput, secondWord, counter);
                separateWord(userInput, thirdWord, counter);
                move(secondWord, thirdWord, tester, jsonObject, jsonArray);
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if(firstWord == "save") {
            if (openCalled)
            {               
                saveChanges(jsonTXT, tester, jsonObject, jsonArray);
                ofstream outFile(fileName);
                if (outFile.is_open()) {
                    outFile << jsonTXT;

                    outFile.close();
                    std::cout << "File write successful." << std::endl;
                } else {
                    std::cout << "Unable to open the file." << std::endl;
                }
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if(firstWord == "saveas") {
            if (openCalled)
            { 
                fileName = "";
                separateWord(userInput, fileName, counter); 
                jsonTXT = "";            
                saveChanges(jsonTXT, tester, jsonObject, jsonArray);
                ofstream outFile(fileName);
                if (outFile.is_open()) {
                    outFile << jsonTXT;

                    outFile.close();
                    std::cout << "File write successful." << std::endl;
                } else {
                    std::cout << "Unable to open the file." << std::endl;
                }
            }
            else {
                cout << "Please open a file first" << endl;
            }
        }

        else if(firstWord == "exit"){
            return 0;
        }
        
        else {
            cout << "Invalid input" << endl;
        }

        counter = 0;
        getline(cin, userInput);
        separateWord(userInput, firstWord, counter);
    }
    
}