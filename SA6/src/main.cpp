#include <iostream>
#include "../headers/voiture.h"
#include "../headers/parking.h"
#include <fstream>
#include <string.h>
#include <thread>
using namespace std;

int main (void){

    Parking * P2 = new Parking(1, "parking.csv");
    P2->printData();
    Parking * P3 = new Parking(2, "parking.csv");
    P3->printData();

    Voiture * v1 = new Voiture(8, "voitures.csv");
    v1->printData();
    v1->communicateServer(8080);

    Voiture * v2 = new Voiture(12, "voitures.csv");
    v2->printData();
    v2->communicateServer(8080);

    //Parking * P1 = new Parking(0, 2, 10, "parking.csv");
    //P1->AfficherInfo();
    
    //string tab[4] = {"1","0","0","0"}; //nb heures, handicap, âge, statut
    //P2->calcul_prix(tab);


    //v1->communicateServer(P2->getPort());
    //v2->communicateServer(P3->getPort());


    delete v1;
    delete v2;
    delete P2;
    delete P3;
    return 0;
}