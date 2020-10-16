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
    Parking * P1 = new Parking(1, "parking.csv");
    Parking * P2 = new Parking(2, "parking.csv");
    
    Voiture * v1 = new Voiture(8, "voitures.csv");
    Voiture * v2 = new Voiture(12, "voitures.csv");
    Voiture * v3 = new Voiture(18, "voitures.csv");

    thread * tp1 = new thread(startServer, P1); 
    thread * tp2 = new thread(startServer, P2);

    tp1->detach();
    tp2->detach();

    sleep(3);
    //Alternative au sleep ? ..

    thread * tv1 = new thread(connexionServer, v1, 8080); // EN théorie on récupère le port du server depuis getPort() dans le parking
                                                          // On peux donc imaginer un while(!parkingTrouve) puis on puise dans une liste de parking
                                                          // et l'on se connecte tant qu'on ne trouve pas un accord. 
    thread * tv2 = new thread(connexionServer, v2, 8080); 
    thread * tv3 = new thread(connexionServer, v3, 8081);

    tv1->join();
    tv2->join();
    tv3->join();

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

    delete tp1;
    delete tp2;
    delete tv1;
    delete tv2;
    delete tv3;
    delete v1;
    delete v2;
    delete P1;
    delete P2;
    return 0;
}