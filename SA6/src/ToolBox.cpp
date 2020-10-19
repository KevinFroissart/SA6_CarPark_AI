#include "../headers/ToolBox.hpp"
#include <sstream>
#include <iterator>

ToolBox::ToolBox(){}

/**
 * @brief Read a CSV file at a specific line.
 *
 * @param file the name of the CSV file.
 * @param id the line number containing the sought information.
 * @throw runtime_error Thrown if `file` could not be opened.
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
 * @brief Write in a CSV file at a specific line. Not done yet.
 *
 * @param file the name of the CSV file.
 * @param id the line number containing the sought information.
 * @throw runtime_error Thrown if `file` could not be opened.
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
 * @brief Convert a tab of floats into a single string.
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

/**
 * @brief Convert a string to a tab of strings
 * 
 * @param msg the string
 * @param delimiter the delimiter
 * @return vector<string> 
 */
vector<string> ToolBox::StringToTab(string msg, char delimiter){

    vector<string> tab;    
    string s = msg;

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        tab.push_back(token);
        s.erase(0, pos + 1);
    }   
    tab.push_back(s);
    return tab;
}