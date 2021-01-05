#ifndef MAIN_BACK_HPP
#define MAIN_BACK_HPP
#include "../headers/Voiture.hpp"
#include "../headers/Parking.hpp"
#include <string.h>
#include <thread>
#include <pthread.h>

using namespace std;

class Main_back
{
public:
    Main_back();
    ~Main_back();
    int m_nbParking;
    int m_nbVoiture;
    int process();
    vector<Parking *> m_listeParking;
    map<int, map<int, string>> conversation;

private:
    vector<Parking *> m_listeParking_shuffle;
    vector<thread *> m_listeThreadParking;
    vector<Voiture *> m_listeVoiture;
    vector<Voiture *> m_listeVoitureTmp;
};

#endif