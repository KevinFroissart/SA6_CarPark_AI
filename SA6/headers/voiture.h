#ifndef VOITURE_H
#define VOITURE_H
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Voiture{
    public:
        Voiture(int id, string filePath); //constructeur utilisant les informations du csv
        Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure); //constructeur utilisant les informations données en paramètre
        ~Voiture();
        void printData();
        float calcul_prix();

    private:
        float prixVoulu;
        int v_id;
        string v_path;   //chemin du csv dans lequel on récupère les informations de la voiture
        string v_name; //nom de la voiture (optionel)
        string v_marque; //marque de la voiture
        string v_statut; //statut social
        string v_handicap;
        string v_age;
        string v_heure; //durée demandée pour le stationement
        int v_prixBase;
        vector<float> v_tab; //tableau de int contenant les informations à envoyer au parking
        vector<float> v_tab_facteurs; 
        vector<float> initTab(); //méthode initialisant le tableau 'v_tab'
        bool rechercheParking;
        void InterrogerParking(); //crée la requête dans le tampon pour interroger un parking
        bool EcouterReponseParking(); //se met à l'écoute d'une réponse du parking
};

#endif