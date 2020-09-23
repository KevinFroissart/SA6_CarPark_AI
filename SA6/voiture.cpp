#include "voiture.h"
#include "CSVManager.h"
#include <sstream>

Voiture::Voiture(int id, string filePath) : m_id(id), m_path(filePath){

    CSVManager CSVm;    
    string input,m_line = CSVm.CSVReader(m_path, m_id);

    stringstream input_stringstream(input);

    getline(input_stringstream, m_name, ',');
    getline(input_stringstream, m_marque, ',');
}

Voiture::Voiture(int id, string name, string marque) : m_id(id), m_name(name), m_marque(marque){

}

Voiture::~Voiture(){
    //destructeur
}

void Voiture::printData(){

    cout << "id : " << m_id << " | Nom de la voiture : " << m_name << " | Marque : " << m_marque << endl;
}