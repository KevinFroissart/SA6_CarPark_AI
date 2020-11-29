#include "../headers/ToolBox.hpp"

namespace tb {

    /**
     * @brief Read a CSV file at a specific line.
     * @param file the name of the CSV file.
     * @param id the line number containing the sought information.
     * @throw std::runtime_error Thrown if `file` could not be opened.
     * @return the line read in the CSV.
     */
    std::string CSVReader(std::string file, int id){
        std::fstream myFile(file);
        if(!myFile.is_open()) throw std::runtime_error("Could not open file");

        int lineNumber = 0;
        std::string tmp;
        std::string line;

        while(myFile.good()){
            ++lineNumber == id ? getline(myFile, line, '\n') : getline(myFile, tmp, '\n');
        }
        myFile.close();
        return line;
    }

    /**
     * @brief Write in a CSV file at a specific line. Not done yet.
     * @param path the file path
     * @param file the name of the CSV file.
     * @param id the line number containing the sought information.
     * @throw std::runtime_error Thrown if `file` could not be opened.
     * @return true, false if nothing was written in the file.
     */
    bool CSVWriterParkLogs(std::string path, std::string file, std::string id){
        
        std::ifstream filein(path + file);
        std::ofstream fileout(path + "updated" + file);
        if(!filein.is_open() || !fileout.is_open()) throw std::runtime_error("Could not open file");

        std::string nbPassage = "1";
        bool existe = false;

        std::string tmp;
        while(std::getline(filein, tmp)){
            if(tmp.substr(0, tmp.find(",")) == id){
                nbPassage = tmp.substr(tmp.find(",")+1, tmp.size());
                tmp = id + "," + std::to_string(stoi(nbPassage) + 1);
                existe = true;
            }
            tmp += "\n";
            fileout << tmp;
        }
        
        if(!existe) tmp += id + "," + nbPassage + "\n";
        fileout << tmp;

        std::string s_str = path;
        s_str += "updated" + file;
        std::string n_str = path + file;
        const char * oldname = s_str.c_str();
        const char * newname = n_str.c_str();

        if(remove(newname) != 0) perror("Error deleting file");
        if(rename(oldname, newname) != 0) perror("Error renaming file");
        return true;
    }

    /**
     * @brief Convert a tab of floats into a single string.
     * @param tab the tab to convert.
     * @param delimiter the delimiter to be put between each tab element.
     * @return res, the final string.
     */
    std::string floatTabToString(std::vector<float> tab, char delimiter) {
        std::string res = std::to_string((int) tab[0]);
        if(tab.size() > 1) {
            for(unsigned int i = 1; i < tab.size(); i++){
                res += delimiter + std::to_string((int) tab[i]);
            }
        }
        return res;
    }

    /**
     * @brief Convert a string to a tab of strings
     * @param msg the string
     * @param delimiter the delimiter
     * @return vector<string> 
     */
    std::vector<std::string> StringToTab(std::string msg, char delimiter){

        std::vector<std::string> tab;    
        std::string s = msg;

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            tab.push_back(token);
            s.erase(0, pos + 1);
        }   
        tab.push_back(s);
        return tab;
    }

    /**
     * @brief Counts the number of line of a file
     * @param file 
     * @return int 
     */
    int getNbLines(std::string file){
        std::fstream filein(file);
        if(!filein.is_open()) throw std::runtime_error("Could not open file");
        
        int nb_line = 0;
        std::string tmp;

        while(getline(filein, tmp)){
            ++nb_line;
        }

        filein.close();
        return nb_line;
    }
}