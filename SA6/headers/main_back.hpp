#ifndef MAIN_BACK_HPP
#define MAIN_BACK_HPP
#include "../headers/Voiture.hpp"
#include "../headers/Parking.hpp"
#include "../headers/ToolBox.hpp"
#include <string.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <map>

using namespace std;

class Main_back{
    public:
        Main_back();
        ~Main_back();
        int m_nbParking;
        int m_nbVoiture;
        int process();
        vector<Parking *> m_listeParking;
        map<int, map<int, string>> conversation;
        map<int, float> caisseParking;

    private:
        vector<thread *> m_listeThreadParking;
        vector<Voiture *> m_listeVoiture;
        vector<Voiture *> m_listeVoitureTmp;
};

#endif