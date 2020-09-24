#include "parking.h"
#include "CSVManager.h"
#include <sstream>
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



Parking::Parking(int id, string cheminFichier){

    CSVManager CSVm;    
    string input,m_line = CSVm.CSVReader(cheminFichier, id);

    stringstream input_stringstream(input);

    getline(input_stringstream, s_idParking, ',');
    getline(input_stringstream, s_prixBase, ',');
    getline(input_stringstream, s_remplissage, ',');
    getline(input_stringstream, s_capacite, ',');

    /*idParking = stoi(s_idParking);
    prixBase = stoi(s_prixBase);
    remplissage = stoi(s_remplissage);
    capacite = stoi (s_capacite);*/
}


Parking::~Parking(){
//destructeur
}


bool Parking::EstRempli(){
    return (remplissage == capacite);
}

void Parking::AfficherInfo(){
    cout<<"id: " << idParking<<" | " << "prix de base: " << prixBase <<" | "<< "remplissage actuel: "<< remplissage <<"/"<< capacite <<endl;
}

