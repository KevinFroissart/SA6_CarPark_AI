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
        float calcul_prix(vector<string> tab);    //prend un tableau de donnée issues de la voiture, et calcule un prix un adapté, en prenant également en compte le remplissage
        int getPort();
        string protocoleCommunication(string message, int etape);
        bool demarerServer();

    private:
        vector<string> idVoiture;
        float s_prix;
        string s_infoVoiture;
        string s_port;
        string s_prixBase;
        string s_idParking;
        string s_remplissage;
        string s_capacite;
        string filePath;
        int tab_current_car[];  //contient les données de la voiture actuellement examinée
        bool EstRempli();
        string ajouterVoiture();
        int readLog(int id);
};

#endif