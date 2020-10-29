#include <iostream>
#include "../headers/voiture.hpp"
#include "../headers/parking.hpp"
#include "../headers/ToolBox.hpp"
#include <fstream>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
using namespace std;

void startServer(Parking * P){
    if(!P->demarerServer()) cout << "Le parking ne parviens pas à démarrer le serveur" << endl;
}

void connexionServer(Voiture * v, int port){
    if(!v->connexionServer(port)) cout << "La voiture ne parviens pas à se connecter au serveur" << endl;
}

int main (void){

    ToolBox tb;

    int nb_parking = 3;
    vector<Parking *> listeParking;
    vector<thread *> listeThreadParking;

    for(int i = 0; i < nb_parking; i++){
        listeParking.push_back(new Parking(i+1, "parking.csv"));  
        listeThreadParking.push_back(new thread(startServer, listeParking[i]));
        listeThreadParking[i]->detach();
    }

    sleep(3);

    int nb_voiture = 30;
    vector<Voiture *> listeVoiture;
    vector<Voiture *> listeVoitureTmp;

    for(int i = 0; i < nb_voiture; i++){
        listeVoitureTmp.push_back(new Voiture(i + 1, "voitures.csv"));
    }

    //Ajouter des voitures de manière aléatoire dans notre liste
    while(listeVoiture.size() != (unsigned int) nb_voiture){
        srand(time(NULL));
        int voitureRand = rand() % (int) listeVoitureTmp.size();
        
        listeVoiture.push_back(new Voiture(listeVoitureTmp[voitureRand]->getID(), "voitures.csv"));
        listeVoitureTmp.erase(listeVoitureTmp.begin() + voitureRand);
    }

    //Creer les threads pour chaque voitures
    for(int i = 0; i < nb_voiture; i++){
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
    for(Voiture* voiture : listeVoiture){
        delete voiture;
    }
    return 0;
}