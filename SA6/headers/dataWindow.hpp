#ifndef DATAWINDOW_HPP
#define DATAWINDOW_HPP
#include <string.h>

using namespace std;

class dataWindow
{
public:
    dataWindow(int idParking);
    int newWindow();

private:
    int id_parking;
};

#endif