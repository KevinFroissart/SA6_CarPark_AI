#ifndef PARKING_HPP
#define PARKING_HPP
#include <iostream>
#include <thread>
#include <fstream>
using namespace std;

class Parking{
    public:
        Parking(int id, float defaultPrice, int capacite_max, string cheminFichier);
        Parking(int id, string cheminFichier);
        ~Parking();
        void printData();
        float calcul_prix(string tab[]);    //prend un tableau de donnée issues de la voiture, et calcule un prix un adapté, en prenant également en compte le remplissage
        int getPort();
        string protocoleCommunication(string message);
        bool demarerServer();

    private:
        string s_port;
        string s_prixBase;
        string s_idParking;
        string s_remplissage;
        string s_capacite;
        string filePath;
        int tab_current_car[];  //contient les données de la voiture actuellement examinée
        bool EstRempli();
        void RajouterVoiture();
        float RepondreVoiture(string tab[]);                         //lorsque une requête voiture est reçu, va calculer un prix et retourner oui, non (si plein)
        float RepondreVoiture2(float prix_propose, string tab[]);    //si la 1ere offre a été refusé par la voiture, analyse la contre-offre de celle-ci
};

#endif