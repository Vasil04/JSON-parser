#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include "KVPairs.hpp"
#include "Controller.hpp"

using std::string, std::cin, std::cout, std::map, std::ifstream, std::endl;
using namespace MyController;

int main(){

    string jsonTXT;

    // getline(cin, jsonTXT);

    ifstream file("JSONTXT.json");

    if (!file.is_open()){
        cout << "Error opening the file";
        return -1;
    }

    while (!file.eof()){
        getline(file, jsonTXT);
    }

    file.close();

    cout << validate(jsonTXT);
    
}