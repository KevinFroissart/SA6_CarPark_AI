#ifndef CSVMANAGER_H
#define CSVMANAGER_H
#include <iostream>
#include <fstream>

using namespace std;

class CSVManager{
    public:
        CSVManager();
        string CSVReader(string file, int id);
        bool CSVWriter(string file);

    private:
        

};


#endif
