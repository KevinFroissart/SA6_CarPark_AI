#ifndef PARKING_HPP
#define PARKING_HPP
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
using namespace std;

class Parking{
    public:
        Parking(int id, float defaultPrice, int capacite_max, string cheminFichier);
        Parking(int id, string cheminFichier);
        ~Parking();
        int getPort();
        bool demarerServer();
        string protocoleCommunication(string message, int etape);

    private:
        float s_prix;
        string filePath;
        string s_infoVoiture;
        string s_parkingData[5];
        vector<string> idVoiture;
        
        bool EstRempli();
        int readLog(int id);
        string ajouterVoiture();
        float calcul_prix(vector<string> tab);
};

#endif