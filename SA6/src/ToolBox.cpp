#include "../headers/ToolBox.hpp"
#include <sstream>
#include <iterator>

ToolBox::ToolBox(){}

/**
 * @brief Read a CSV file at a specific line.
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
 * @brief Write in a CSV file at a specific line. Not done yet.
 *
 * @param file the name of the CSV file.
 * @param id the line number containing the sought information.
 * @throw std::runtime_error Thrown if `file` could not be opened.
 * @return true, false if nothing was written in the file.
 */
bool ToolBox::CSVWriterParkLogs(string file, string id){
    
    fstream filein(file);
    ofstream fileout("updated" + file);
    if(!filein.is_open() || !fileout.is_open()) throw runtime_error("Could not open file");

    string nbPassage = "0";
    bool existe = false;

    string tmp;
    while(getline(filein, tmp)){
        if(tmp.substr(0, tmp.find(",")) == id){
            nbPassage = tmp.substr(tmp.find(",")+1, tmp.size());
            tmp = id + "," + to_string(stoi(nbPassage) + 1);
            cout << id << " et " << tmp << endl;
            existe = true;
        }
        tmp += "\n";
        fileout << tmp;
    }
    
    if(!existe) tmp += id + "," + nbPassage + "\n";
    fileout << tmp;

    string s_str = "updated" + file;
    const char * oldname = s_str.c_str();
	const char * newname = file.c_str();

    if(remove(newname) != 0) perror("Error deleting file");
    if(rename(oldname, newname) != 0) perror("Error renaming file");
    return true;
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