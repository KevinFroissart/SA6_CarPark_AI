#include <iostream>
#include "voiture.h"
#include "parking.h"
#include <fstream>
#include <string.h>
#include <thread>
using namespace std;

int main (void){

    Voiture * v1 = new Voiture(8, "voitures.csv");
    Voiture * v2 = new Voiture(16, "Voiture n°16", "Porsche");
    v1->printData();
    v2->printData();
    
    Parking * P1 = new Parking(0, 2, 10, "parking.csv");
    P1->AfficherInfo();
    /* Parking * P2 = new Parking(0, "parking.csv");
    P2->AfficherInfo();        probleme avec la conversion string>int pour la lecture csv */

    delete v1;
    delete v2;
    delete P1;
    return 0;
}