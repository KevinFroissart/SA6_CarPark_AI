#include "../headers/parking.h"
#include "../headers/ToolBox.h"
#include <sstream>
#include <vector>
#include <math.h>

Parking::Parking(int id, float defaultPrice, int capacite_max, string cheminFichier) : filePath(cheminFichier){
    s_prixBase = defaultPrice;
    s_idParking = id;
    s_remplissage = '0';
    s_capacite = capacite_max;

    ofstream File(filePath);
    if (File.is_open()){
        File<<s_idParking << "," << s_prixBase << "," << s_remplissage << "," << s_capacite <<"\n";
        File.close();
    } else
        throw runtime_error("Could not open file");
}

Parking::Parking(int id, string cheminFichier) : filePath(cheminFichier){
    ToolBox tb;    
    string input = tb.CSVReader(filePath, id);

    stringstream input_stringstream(input);

    getline(input_stringstream, s_idParking, ',');
    getline(input_stringstream, s_prixBase, ',');
    getline(input_stringstream, s_remplissage, ',');
    getline(input_stringstream, s_capacite, ',');
    getline(input_stringstream, s_port, ',');
}

Parking::~Parking(){
//destructeur
}

bool Parking::EstRempli(){
    return (s_remplissage == s_capacite);
}

void Parking::printData(){
    cout<<"id: "<<s_idParking<<" | prix de base: "<< s_prixBase<<" | remplissage actuel: "<<s_remplissage<<"/"<<s_capacite<< endl;
}

float Parking::calcul_prix(string tab[]){
    vector <float> tab_facteurs;
    float prix = (float) stoi(s_prixBase);
    // la 1ere case du vector est la durée
    tab_facteurs.push_back( (float)stoi(tab[0]) );              //facteur durée
    float nb_heures = tab_facteurs[0]; 

    tab_facteurs.push_back(1 - 0.25 * (float)stoi(tab[1]) );    //Facteur handicap
    tab_facteurs.push_back(1 - 0.25 * (float)stoi(tab[2]) );    //facteur age (jeune, adulte, vieux)
    tab_facteurs.push_back(1 - 0.25 * (float)stoi(tab[3]) );    //facteur statut social

    float somme_facteur = 0;
    for(unsigned int i = 1; i<tab_facteurs.size(); i++){
        somme_facteur = somme_facteur + tab_facteurs[i];
    }
    cout<<"prix 1 = "<<prix<<endl;

    prix = prix * ((somme_facteur / (tab_facteurs.size()-1))        //moyenne des facteurs (compris entre 0 et 2) sauf la durée
                * (nb_heures*0.7 + 0.3*(float)log(nb_heures))   // fois le nombre d'heures (et un logarithme)
                * 1 + 0.75*((float)(stoi(s_remplissage)) /      //pondéré par le remplissage actuel du parking
                            (float)(stoi(s_capacite))));
    cout<<"prix après réduction = "<<prix<<endl;
    return prix;
}

float Parking::RepondreVoiture(string tab[]){
    if(s_remplissage<s_capacite){
        float prix = calcul_prix(tab);
        cout<<"le parking" << s_idParking << "n'est pas rempli. Il propose le prix suivant"<<prix<<endl;
        return prix;
    }
    else {
        cout<<"le parking" << s_idParking << "est rempli"<<endl;
        return -1;
    }
}

float Parking::RepondreVoiture2(float prix_propose, string tab[]){
    float prix = calcul_prix(tab);
    if (prix_propose> (0.85 * prix)){
        cout<<"le parking" << s_idParking << "n'est pas rempli. Il accepte l'offre de "<<prix_propose<<"€"<<endl;
        //s_remplissage++;
        return prix;
    }
    else{
        cout<<"le parking "<<s_idParking<<" n'accepte pas la proposition de la voiture";
        return -1;
    }
} 

int Parking::getPort() {
    return stoi(s_port);
}