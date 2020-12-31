#ifndef TOOLBOX_HPP
#define TOOLBOX_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#pragma once

namespace tb
{
    std::string CSVReader(std::string file, int id);
    bool CSVWriterParkLogs(std::string path, std::string file, std::string idVoiture);
    std::string floatTabToString(std::vector<float> tab, char delimiter);
    std::vector<std::string> StringToTab(std::string tab, char delimiter);
    bool LogSorter(std::string file);
    int getNbLines(std::string file);
    int readLog(int id, std::string path);
} // namespace tb

#endif