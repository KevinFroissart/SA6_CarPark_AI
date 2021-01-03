#ifndef DATAWINDOW_HPP
#define DATAWINDOW_HPP
#include "../headers/main_back.hpp"
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <map>

using namespace std;

class dataWindow
{
public:
    dataWindow(int idParking, Main_back *main_b);
    int newWindow();

private:
    string currentConv;
    int id_parking;
    Main_back *main_b;
};

#endif