#ifndef PARKING_H
#define PARKING_H
#include <iostream>
#include <thread>
#include <fstream>
using namespace std;


class Parking{
    public:
        Parking(int id, float defaultPrice, int capacite_max, string cheminFichier);
        void AfficherInfo();

    private:
        float prixBase;
        int idParking;
        int remplissage;
        int capacite;
        string filePath;
        bool EstRempli();
        bool RepondreVoiture();     //lorsque une requête voiture est reçu, va répondre oui, non (si plein), ou proposer une contre offre//

};


#endif
