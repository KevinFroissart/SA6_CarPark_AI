#include "../headers/ToolBox.h"

ToolBox::ToolBox(){}

/**
 * Read a CSV file at a specific line.
 *
 * @param file the name of the CSV file.
 * @param id the line number containing the sought information.
 * @throw std::runtime_error Thrown if `file` could not be opened.
 * @return the line read in the CSV.
 */
string ToolBox::CSVReader(string file, int id){
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
bool ToolBox::CSVWriter(string file){
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

/**
 * Convert a tab of floats into a single string.
 *
 * @param tab the tab to convert.
 * @param delimiter the delimiter to be put between each tab element.
 * @return res, the final string.
 */
string ToolBox::floatTabToString(vector<float> tab, char delimiter) {
    string res = to_string((int) tab[0]);
    if(tab.size() > 1) {
        for(unsigned int i = 1; i < tab.size(); i++){
            res += delimiter + to_string((int) tab[i]);
        }
    }
    return res;
}