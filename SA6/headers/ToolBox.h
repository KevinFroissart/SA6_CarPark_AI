#ifndef TOOLBOX_H
#define TOOLBOX_H
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

    private:
};

#endif
