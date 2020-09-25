#include "CSVManager.h"

CSVManager::CSVManager(){}

/**
 * Read a CSV file at a specific line.
 *
 * @param file the name of the CSV file.
 * @param id the line number containing the sought information.
 * @throw std::runtime_error Thrown if `file` could not be opened.
 * @return the line read in the CSV.
 */
string CSVManager::CSVReader(string file, int id){
    fstream myFile(file);
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    int lineNumber = 0;
    string tmp;
    string line;

    while(myFile.good()){
        ++lineNumber == id ? getline(myFile, line, '\n') : getline(myFile, tmp, '\n');
    }
    myFile.close();
    return line;
}

/**
 * Write in a CSV file at a specific line.
 *
 * @param file the name of the CSV file.
 * @param id the line number containing the sought information.
 * @throw std::runtime_error Thrown if `file` could not be opened.
 * @return true, false if nothing was written in the file.
 */
bool CSVManager::CSVWriter(string file){
    bool done = true;

    ofstream File(file);
    if (File.is_open()){
        
        File.close();
    }else{
        done = false;
        throw runtime_error("Could not open file");
    }
    return done;
}