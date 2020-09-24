#ifndef VOITURE_H
#define VOITURE_H
#include <iostream>
#include <fstream>


class Voiture{
    public:
        Voiture(int id, std::string filePath); //constructeur utilisant les informations du csv
        Voiture(int id, std::string name, std::string marque); //constructeur utilisanr les informations données en paramètre
        ~Voiture();
        void printData();

    private:
        float prixVoulu;
        int m_id;
        std::string m_path;   //chemin du csv dans lequel on récupère les informations de la voiture
        std::string m_line; //ligne dans laquelle on stocke toutes les informations lues dans le csv
        std::string m_name; //nom de la voiture (optionel)
        std::string m_marque; //marque de la voiture
        std::string m_statut; //statut social
        std::string m_handicap;
        std::string m_age;
        bool rechercheParking;
        void InterrogerParking(); //crée la requête dans le tampon pour interroger un parking
        bool EcouterReponseParking(); //se met à l'écoute d'une réponse du parking
};


#endif
