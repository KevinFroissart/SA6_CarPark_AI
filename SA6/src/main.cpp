#include <iostream>
#include "../headers/voiture.h"
#include "../headers/parking.h"
#include <fstream>
#include <string.h>
#include <thread>
using namespace std;

int main (void){

    Voiture * v1 = new Voiture(8, "voitures.csv");
    //Voiture * v2 = new Voiture(16, "Voiture n°16", "Porsche", "chômeur", "non", "25", "12");
    v1->printData();
    v1->calcul_prix();
    //v2->printData();

    //Parking * P1 = new Parking(0, 2, 10, "parking.csv");
    //P1->AfficherInfo();
    Parking * P2 = new Parking(1, "parking.csv");
    P2->printData();
    string tab[4] = {"1","0","0","0"}; //nb heures, handicap, âge, statut
    P2->calcul_prix(tab);

    delete v1;
    //delete v2;
    delete P2;
    return 0;
}