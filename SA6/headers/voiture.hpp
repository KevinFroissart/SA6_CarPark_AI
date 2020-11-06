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
        int getID();
        bool rechercheParking;
        bool connexionServer(int port, int id);
        
    private:
        int v_etape; //etape du protocole de communication
        int v_id; //id de la voiture
        int idParking;
        int v_prixBase;
        float prixVoulu;
        string logPath; //chemin du csv dans lequel on stock les l'historique de la voiture
        string v_path;   //chemin du csv dans lequel on récupère les informations de la voiture
        string v_voitureData[6]; //tableau contenant les infos de la voiture
        vector<float> v_tab; //tableau de int contenant les informations à envoyer au parking

        float calcul_prix();
        vector<float> initTab(); //méthode initialisant le tableau 'v_tab'
        string protocoleCommunication(string message);
        bool communicateWithParking(SocketVoiture client, string replyServer);
};

#endif