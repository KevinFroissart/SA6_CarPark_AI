#include "voiture.h"
#include "CSVManager.h"
#include <sstream>

Voiture::Voiture(int id, string filePath) : m_id(id), m_path(filePath){
    CSVManager CSVm;    
    string input,m_line = CSVm.CSVReader(m_path, m_id);

    stringstream input_stringstream(input);

    getline(input_stringstream, m_name, ',');
    getline(input_stringstream, m_marque, ',');
    getline(input_stringstream, m_statut, ',');
    getline(input_stringstream, m_handicap, ',');
    getline(input_stringstream, m_age, ',');
}

Voiture::Voiture(int id, string name, string marque, string statut, string handicap, string age) : 
m_id(id), m_name(name), m_marque(marque), m_statut(statut), m_handicap(handicap), m_age(age){

}

Voiture::~Voiture(){
    //destructeur
}

void Voiture::printData(){
    cout<<"id: "<<m_id<<" | Nom de la voiture: "<<m_name<<" | Marque: "<< m_marque <<" | Statut: "<< m_statut<<" | Handicap: "<<m_handicap<<" | age: "<<m_age<< endl;
}