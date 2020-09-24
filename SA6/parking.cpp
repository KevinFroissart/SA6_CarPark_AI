#include "parking.h"
#include "CSVManager.h"
#include <sstream>

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



Parking::Parking(int id, string cheminFichier){

    CSVManager CSVm;    
    string input,m_line = CSVm.CSVReader(cheminFichier, id);

    stringstream input_stringstream(input);

    getline(input_stringstream, id, ',');
    getline(input_stringstream, prix, ',');
    getline(input_stringstream, remplissage, ',');
    getline(input_stringstream, capacite, ',');
}


bool Parking::EstRempli(){
    return (remplissage == capacite);
}

void Parking::AfficherInfo(){
    cout<<"id: " << idParking<<" | " << "prix de base: " << prixBase <<" | "<< "remplissage actuel: "<< remplissage <<"/"<<capacite <<endl;
}

