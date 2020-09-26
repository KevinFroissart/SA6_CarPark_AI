#include "voiture.h"
#include "CSVManager.h"
#include <sstream>

Voiture::Voiture(int id, string filePath) : v_id(id), v_path(filePath){
    CSVManager CSVm;    
    string input = CSVm.CSVReader(v_path, v_id);

    stringstream input_stringstream(input);

    getline(input_stringstream, v_name, ',');
    getline(input_stringstream, v_marque, ',');
    getline(input_stringstream, v_statut, ',');
    getline(input_stringstream, v_handicap, ',');
    getline(input_stringstream, v_age, ',');
    getline(input_stringstream, v_heure, ',');

    initTab();
}

Voiture::Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure) : 
v_id(id), v_name(name), v_marque(marque), v_statut(statut), v_handicap(handicap), v_age(age), v_heure(heure){

    initTab();
}

Voiture::~Voiture(){
    //destructeur
}

void Voiture::printData(){
    cout<<"id: "<<v_id<<" | "<<v_name<<" | Marque: "<<v_marque <<" | Statut: "<<v_statut<<" | Handicap: "<<v_handicap<<" | age: "<<v_age<<" | heure: "<<v_heure<<endl;
    cout <<"tab: id: "<<v_tab[0]<<" | heures: "<<v_tab[1]<<" | handicap: "<<v_tab[2]<<" | classe d'age: "<<v_tab[3]<<" | statut: "<<v_tab[4]<<endl;
}

vector<int> Voiture::initTab(){
    v_tab.push_back(v_id);
    v_tab.push_back(stoi(v_heure));
    v_tab.push_back(v_handicap == "oui" ? 1 : 0); // si Vrai = 1 sinon = 0
    v_tab.push_back(stoi(v_age) < 60 ? stoi(v_age) < 25 ? 1 : 0 : 2); //age > 60 = 2 | age < 25 = 1 sinon 0
    v_tab.push_back(v_statut == "salarié" ? 1 : v_statut == " patron" ? 0 : 2); //salarié = 1 | patron = 2 sinon 0
    return v_tab;
} 