#include <iostream>
#include "../headers/voiture.hpp"
#include "../headers/parking.hpp"
#include <fstream>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void startServer(Parking * P){
    if(!P->demarerServer()) cout << "Le parking ne parviens pas à démarrer le serveur" << endl;
}

void connexionServer(Voiture * v, int port){
    if(!v->connexionServer(port)) cout << "La voiture ne parviens pas à se connecter au serveur" << endl;
}

int main (void){

    int nb_parking = 3;
    vector<Parking *> listeParking;
    vector<thread *> listeThreadParking;

    for(int i = 0; i < nb_parking; i++){
        listeParking.push_back(new Parking(i+1, "parking.csv"));  
        listeThreadParking.push_back(new thread(startServer, listeParking[i]));
        listeThreadParking[i]->detach();
    }

    sleep(3);

    int nb_voiture = 3;
    vector<Voiture *> listeVoiture;

    for(int i = 0; i < nb_voiture; i++){
        listeVoiture.push_back(new Voiture(i+1, "voitures.csv"));
        for(int j = 0; j < nb_parking && listeVoiture[i]->rechercheParking; j++){
            thread * tmp = new thread(connexionServer, listeVoiture[i], listeParking[j]->getPort());
            tmp->join();
            delete tmp;
        }
        cout << (listeVoiture[i]->rechercheParking ? "La voiture n'as pas trouvé de parking" : "La voiture a trouvé un parking");
        cout << endl;
    }

    for(int i = 0; i < nb_parking; i++){
        delete listeThreadParking[i];
        delete listeParking[i];
    }      
    for(int i = 0; i < nb_voiture; i++){
        delete listeVoiture[i];
    }

    return 0;
}