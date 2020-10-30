#ifndef VOITURE_HPP
#define VOITURE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../headers/SocketVoiture.hpp"

using namespace std;

class Voiture{
    public:
        Voiture(int id, string filePath); //constructeur utilisant les informations du csv
        Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure); //constructeur utilisant les informations données en paramètre
        ~Voiture();
        float calcul_prix();
        bool connexionServer(int port);
        bool rechercheParking;
        int getID();
        
    private:
        int v_etape; //etape du protocole de communication
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
        vector<float> initTab(); //méthode initialisant le tableau 'v_tab'
        string protocoleCommunication(string message);
        bool communicateWithParking(SocketVoiture client, string replyServer);
};

#endif