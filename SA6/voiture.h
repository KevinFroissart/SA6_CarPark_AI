#ifndef VOITURE_H
#define VOITURE_H
#include <iostream>
#include <thread>
#include <fstream>


class Voiture{
    public:
        Voiture(int id, std::string filePath);

    private:
        float prixVoulu;
        int m_id;
        std::string m_path;   //chemin du csv dans lequel on récupère les informations de la voiture
        bool rechercheParking;
        void InterrogerParking();   //crée la requête dans le tampon pour interroger un parking
        bool EcouterReponseParking();    //se met à l'écoute d'une réponse du parking
};


#endif
