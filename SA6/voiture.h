#ifndef VOITURE_H
#define VOITURE_H
#include <iostream>
#include <fstream>

using namespace std;

class Voiture{
    public:
        Voiture(int id, string filePath); //constructeur utilisant les informations du csv
        Voiture(int id, string name, string marque, string statut, string handicap, string age); //constructeur utilisant les informations données en paramètre
        ~Voiture();
        void printData();

    private:
        float prixVoulu;
        int m_id;
        string m_path;   //chemin du csv dans lequel on récupère les informations de la voiture
        string m_line; //ligne dans laquelle on stocke toutes les informations lues dans le csv
        string m_name; //nom de la voiture (optionel)
        string m_marque; //marque de la voiture
        string m_statut; //statut social
        string m_handicap;
        string m_age;
        string m_heure; //durée demandée pour le stationement 
        bool rechercheParking;
        void InterrogerParking(); //crée la requête dans le tampon pour interroger un parking
        bool EcouterReponseParking(); //se met à l'écoute d'une réponse du parking
};

#endif