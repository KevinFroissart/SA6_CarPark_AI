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

    //int nb_parking = 2;
    Parking * P2 = new Parking(1, "parking.csv");
    
    Voiture * v1 = new Voiture(8, "voitures.csv");
    Voiture * v2 = new Voiture(12, "voitures.csv");

    thread * t1 = new thread(startServer, P2); 
    t1->detach();

    sleep(2);

    thread * t2 = new thread(connexionServer, v1, 8080);
    thread * t3 = new thread(connexionServer, v2, 8080);

    t2->join();
    t3->join();

    // cout<<"id du thread : "<<t1.get_id()<<endl;
    //Parking * P3 = new Parking(2, "parking.csv");
    //P3->printData();


   /* vector<Parking> tab_parking;
    for (int i= 0; i<nb_parking; i++){
        tab_parking.push_back(Parking(i, "parking.csv"));
        cout<<endl<<"parking "<<i<<" initialisé"<<endl;
        tab_parking[i].printData();
    }

    vector<thread> tab_threads_parking;
    for (int i =0; i<nb_parking; i++){
        tab_threads_parking.push_back(thread(startServer, tab_parking[i]));
    }

    for (int i =0; i<nb_parking; i++){
        tab_threads_parking[i].join();
    }*/

    delete t1;
    delete t2;
    delete t3;
    delete v1;
    delete v2;
    delete P2;
    return 0;
}