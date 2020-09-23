#include "CSVManager.h"

CSVManager::CSVManager(){}

string CSVManager::CSVReader(string file, int id){
    
    fstream myFile(file);
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    int lineNumber = 0;
    string tmp;
    string line;

    while(myFile.good()){
        ++lineNumber == id ? getline(myFile, line, '\n') : getline(myFile, tmp, '\n');
    }
    
    myFile.close();
    
    return line;
}

string CSVManager::CSVWriter(){

}