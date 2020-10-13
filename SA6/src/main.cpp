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
    //P2->printData();
    cout<<endl<<"debug"<<endl<<endl;
    thread t1(startServer, ref(P2)); 

    //t1.join();
    // cout<<"id du thread : "<<t1.get_id()<<endl;
    //Parking * P3 = new Parking(2, "parking.csv");
    //P3->printData();

    //sleep(2);

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



    Voiture * v1 = new Voiture(8, "voitures.csv");
    Voiture * v2 = new Voiture(12, "voitures.csv");
    
    thread t2(connexionServer, v1, 8080);
    thread t3(connexionServer, v2, 8080);

    //t1.join();
    t2.join();
    t3.join();
    
    
    //v1->connexionServer(8080);

    //v2->connexionServer(8080);


    //Parking * P1 = new Parking(0, 2, 10, "parking.csv");
    //P1->AfficherInfo();
    
    //string tab[4] = {"1","0","0","0"}; //nb heures, handicap, âge, statut
    //P2->calcul_prix(tab);


    //v1->communicateServer(P2->getPort());
    //v2->communicateServer(P3->getPort());


    delete v1;
    delete v2;
    delete P2;
    //delete P3;
    return 0;
}