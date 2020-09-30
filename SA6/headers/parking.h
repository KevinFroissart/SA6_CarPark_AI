#ifndef PARKING_H
#define PARKING_H
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

    private:
        string s_prixBase;
        string s_idParking;
        string s_remplissage;
        string s_capacite;
        string filePath;
        int tab_current_car[];  //contient les données de la voiture actuellement examinée
        bool EstRempli();
        bool RepondreVoiture();     //lorsque une requête voiture est reçu, va répondre oui, non (si plein), ou proposer une contre offre//
};

#endif