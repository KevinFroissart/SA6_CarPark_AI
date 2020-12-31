#ifndef DATAWINDOW_HPP
#define DATAWINDOW_HPP
#include <string.h>
#include <map>

using namespace std;

class dataWindow
{
public:
    dataWindow(int idParking, map<int, map<int, string>> conversation);
    int newWindow();

private:
    string currentConv;
    int id_parking;
    map<int, map<int, string>> conversation;
};

#endif