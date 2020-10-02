#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <iostream>
#include <fstream>

using namespace std;

class ToolBox{
    public:
        ToolBox();
        string CSVReader(string file, int id);
        bool CSVWriter(string file);

    private:
};

#endif
