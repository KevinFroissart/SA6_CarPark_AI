#ifndef TOOLBOX_HPP
#define TOOLBOX_HPP
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class ToolBox{
    public:
        ToolBox();
        string CSVReader(string file, int id);
        bool CSVWriter(string file);
        string floatTabToString(vector<float> tab, char delimiter);
        vector<string> StringToTab(string tab, char delimiter);
    private:
};

#endif
