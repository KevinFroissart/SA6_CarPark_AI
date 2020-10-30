#ifndef TOOLBOX_HPP
#define TOOLBOX_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class ToolBox{
    public:
        ToolBox();
        string CSVReader(string file, int id);
        bool CSVWriterParkLogs(string file, string idVoiture);
        string floatTabToString(vector<float> tab, char delimiter);
        vector<string> StringToTab(string tab, char delimiter);
        bool LogSorter(string file);
        int getNbLines(string file);
    private:
};

#endif
