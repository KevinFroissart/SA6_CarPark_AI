#ifndef VOITURE_H
#define VOITURE_H
#include <iostream>
#include <thread>
#include <fstream>


class Voiture{
    public:

    private:
        float prixVoulu;
        int idVoiture;
        bool rechercheParking;
        void InterrogerParking();   //crée la requête dans le tampon pour interroger un parking
        bool EcouterReponseParking();    //se met à l'écoute d'une réponse du parking
};


#endif
