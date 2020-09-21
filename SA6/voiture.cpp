#include "voiture.h"
#include <sstream>

using namespace std;

Voiture::Voiture(int id, string filePath) : m_id(id), m_path(filePath){
    readCSV();
    
    string input = m_line;
    stringstream input_stringstream(input);

    getline(input_stringstream, m_name, ',');
    getline(input_stringstream, m_marque, ',');
}

Voiture::Voiture(int id, string name, string marque) : m_id(id), m_name(name), m_marque(marque){

}

Voiture::~Voiture(){
    //destructeur
}

void Voiture::readCSV(){
    std::fstream myFile(m_path);
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    int lineNumber = 0;
    while(myFile.good()){
        string tmp;
        ++lineNumber == m_id ? getline(myFile, m_line, '\n') : getline(myFile, tmp, '\n');
    }
    myFile.close();
}

void Voiture::printData(){

    cout << "id : " << m_id << " | Nom de la voiture : " << m_name << " | Marque : " << m_marque << endl;
}