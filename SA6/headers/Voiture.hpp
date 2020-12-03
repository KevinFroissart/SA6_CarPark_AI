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
        Voiture(int id, string filePath); 
        Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure);
        ~Voiture();
        int getID();
        bool rechercheParking;
        bool connexionServer(int port, int id);
        
    private:
        int v_etape;
        int v_id;
        int idParking;
        int v_prixBase;
        float prixVoulu;
        string logPath; 
        string v_path;  
        string v_voitureData[6]; 
        vector<float> v_tab; 

        float calcul_prix();
        vector<float> initTab(); 
        string protocoleCommunication(string message);
        bool communicateWithParking(SocketVoiture client, string replyServer);
};

#endif