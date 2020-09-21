#include "parking.h"
#include <iostream>
#include <thread>
#include <fstream>
using namespace std;


Parking::Parking(int id, float defaultPrice, int capacite_max, string cheminFichier){
    prixBase = defaultPrice;
    idParking = id;
    remplissage = 0;
    capacite = capacite_max;
    filePath = cheminFichier;

    ofstream File(filePath);
    if (File.is_open()){
        File<<idParking << "," << prixBase << "," << remplissage << "," << capacite <<"\n";
        File.close();

    }
    else{cout<<"erreur lors de l'ouverture du fichier "<<filePath<<endl;};
}



bool Parking::EstRempli(){
    return (remplissage == capacite);
}

void Parking::AfficherInfo(){
    cout<<"id: " << idParking<<" | " << "prix de base: " << prixBase <<" | "<< "remplissage actuel: "<< remplissage <<"/"<<capacite <<endl;
}

