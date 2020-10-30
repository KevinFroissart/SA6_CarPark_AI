#include "../headers/ToolBox.hpp"

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
bool ToolBox::CSVWriterParkLogs(string file, string idVoiture){
    
    fstream filein(file);
    ofstream fileout("updated" + file);
    if(!filein.is_open() || !fileout.is_open()) throw runtime_error("Could not open file");

    string nbPassage = "1";
    bool existe = false;

    string tmp;
    while(getline(filein, tmp)){
        if(tmp.substr(0, tmp.find(",")) == idVoiture){
            nbPassage = tmp.substr(tmp.find(",")+1, tmp.size());
            tmp = idVoiture + "," + to_string(stoi(nbPassage) + 1);
            existe = true;
        }
        tmp += "\n";
        fileout << tmp;
    }
    
    if(!existe) tmp += idVoiture + "," + nbPassage + "\n";
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


/**
 * @brief Sort a CSV file by ID
 * 
 * @param file the CSV file
 * @param posId the position of the ID
 * @throw std::runtime_error Thrown if `file` could not be opened.
 * @return true if the operation was successful
 * @return false if the operation wasn't successful
 *//*
bool ToolBox::LogSorter(string file){
    bool success = true;
    fstream filein(file);
    ofstream fileout("sorted" + file);

    if(!filein.is_open() || !fileout.is_open()) throw runtime_error("Could not open file");

    string tmp;
    vector<string> tab;
    
    for(int i = 0; i < getNbLines(file); i++){
        tab.push_back("");
    }

    while(getline(filein, tmp)){
        if(tmp.size() > 1){
            int idx = stoi(tmp.substr(0, tmp.find(",")));
            tab.insert(tab.begin() + idx, tmp);
        }
    }

    for(string string : tab){
        fileout << string + "\n";
    }

    string s_str = "sorted" + file;
    const char * oldname = s_str.c_str();
	const char * newname = file.c_str();

    if(remove(newname) != 0) perror("Error deleting file");
    if(rename(oldname, newname) != 0) perror("Error renaming file");

    return success;
}
*/
/**
 * @brief Counts the number of line of a file
 * 
 * @param file 
 * @return int 
 */
int ToolBox::getNbLines(string file){
    fstream filein(file);
    if(!filein.is_open()) throw runtime_error("Could not open file");
    
    int nb_line = 0;
    string tmp;

    while(getline(filein, tmp)){
        ++nb_line;
    }

    filein.close();
    return nb_line;
}