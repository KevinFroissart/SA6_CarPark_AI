#ifndef PARKING_H
#define PARKING_H
#include <iostream>
#include <thread>
#include <fstream>


class Parking{
    private:
        float prixBase;
        int idParking;
        int capacite;
        bool estRempli();
        bool RepondreVoiture();     //lorsque une requête voiture est reçu, va répondre oui, non (si plein), ou proposer une contre offre//

};


#endif
