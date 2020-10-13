#ifndef VOITURE_HPP
#define VOITURE_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include "../headers/TCPSocket.hpp"
#include <thread>

using namespace std;

class Voiture{
    public:
        Voiture(int id, string filePath); //constructeur utilisant les informations du csv
        Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure); //constructeur utilisant les informations données en paramètre
        ~Voiture();
        void printData();
        float calcul_prix();
        bool connexionServer(int port);

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
        bool rechercheParking;
        void InterrogerParking(); //crée la requête dans le tampon pour interroger un parking
        bool EcouterReponseParking(); //se met à l'écoute d'une réponse du parking
        string tabToString(vector<float> tab, char delimiter);
        string protocoleCommunication(string message);
        bool communicateWithParking(TCPSocket client, string replyServer);
        thread t1;
};

#endif