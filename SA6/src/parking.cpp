#include "../headers/parking.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/ServerParking.hpp"
#include <sstream>
#include <math.h>

/**
 * @brief Construct a new Parking:: Parking object
 * 
 * @param id 
 * @param defaultPrice 
 * @param capacite_max 
 * @param cheminFichier 
 */
Parking::Parking(int id, float defaultPrice, int capacite_max, string cheminFichier) : filePath(cheminFichier){
    s_prixBase = defaultPrice;
    s_idParking = id;
    s_remplissage = "0";
    s_capacite = capacite_max;
    ofstream File(filePath);
    if (File.is_open()){
        File<<s_idParking << "," << s_prixBase << "," << s_remplissage << "," << s_capacite <<"\n";
        File.close();
    } else
        throw runtime_error("Could not open file");
}

/**
 * @brief Construct a new Parking:: Parking object
 * 
 * @param id 
 * @param cheminFichier 
 */
Parking::Parking(int id, string cheminFichier) : filePath(cheminFichier){
    ToolBox tb;    
    string input = tb.CSVReader(filePath, id);

    stringstream input_stringstream(input);

    getline(input_stringstream, s_idParking, ',');
    getline(input_stringstream, s_prixBase, ',');
    getline(input_stringstream, s_remplissage, ',');
    getline(input_stringstream, s_capacite, ',');
    getline(input_stringstream, s_port, ',');

    //demarerServer(); Ne peux pas marcher sans les threads
}

/**
 * @brief Destroy the Parking:: Parking object
 */
Parking::~Parking(){
    ServerP::End();
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Parking::EstRempli(){
    return (s_remplissage == s_capacite);
}

/**
 * @brief 
 * 
 */
void Parking::printData(){
    cout<<"id: "<<s_idParking<<" | prix de base: "<< s_prixBase<<" | remplissage actuel: "<<s_remplissage<<"/"<<s_capacite<< endl;
}

/**
 * @brief method that return the port of the server.
 * 
 * @return the port of the server.
 */
int Parking::getPort() {
    return stoi(s_port);
}

/**
 * @brief 
 * 
 * @param tab 
 * @return float 
 */
float Parking::calcul_prix(vector<string> tab){
    vector <float> tab_facteurs;
    s_prix = stof(s_prixBase);
    // la 1ere case du vector est la durée
    tab_facteurs.push_back(stof(tab[0]));              //facteur durée
    float nb_heures = tab_facteurs[0]; 

    tab_facteurs.push_back(1 - 0.25 * stof(tab[1]));    //Facteur handicap
    tab_facteurs.push_back(1 - 0.25 * stof(tab[2]));    //facteur age (jeune, adulte, vieux)
    tab_facteurs.push_back(1 - 0.25 * stof(tab[3]));    //facteur statut social

    float somme_facteur = 0;
    for(unsigned int i = 1; i<tab_facteurs.size(); i++){
        somme_facteur = somme_facteur + tab_facteurs[i];
    }

    s_prix = s_prix * ((somme_facteur / (tab_facteurs.size()-1))        //moyenne des facteurs (compris entre 0 et 2) sauf la durée
                * (nb_heures*0.7 + 0.3*(float)log(nb_heures))   // fois le nombre d'heures (et un logarithme)
                * 1 + 0.75*(((float) stoi(s_remplissage)) /      //pondéré par le remplissage actuel du parking
                            ((float) stoi(s_capacite))));
    return s_prix;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Parking::demarerServer(){
	if(!ServerP::Start())
	{
		std::cout << "Erreur initialisation sockets : " << ServerP::GetError() << std::endl;
		return -1;
	}
	//int port;
	std::cout << "Port du serveur > " + s_port << endl;
	//std::cin >> port;
	if (!ServerP::Server(stoi(s_port), this)) // on envoie l'instance de notre parking au serveur pour pouvoir utiliser la méthode protocole depuis le ServerParking
	{
		std::cout << "Serveur termine avec l'erreur " << ServerP::GetError() << std::endl;
	}
	ServerP::End();
    cout << "Serveur terminé" << endl;
	return true;
}

//on fait appel au protocole directement dans la classe ServerPaking
/**
 * @brief 
 * 
 * @param message 
 * @return string 
 */
string Parking::protocoleCommunication(string message, int etape){
    ToolBox tb;
    
    // Vérifie si il reste de la place dans le parking, si non on arrete l'échange, si oui on continu
    
    if(etape == 1) return EstRempli() ? "Non" : "Oui";
    
    if(etape == 2){
        s_infoVoiture = message;        
        return to_string(calcul_prix(tb.StringToTab(message, ',')));
    }
     
    if(etape == 3){
        if(message == "Accepte"){ //Si la voiture accepte ce prix alors on lui reserve une place et on lui indique que c'est bon
            s_remplissage = to_string(stoi(s_remplissage) + 1);
            cout << "remplissage : " << s_remplissage << endl;
            return "OK, place reservé";
        }
        else { //Si la voiture n'accepete pas alors elle nous renvoie son prix
            if(stof(message) > (0.85 * s_prix)){
                s_remplissage = to_string(stoi(s_remplissage) + 1);
                return "Accepte, place réservée";
            } 
            return "Refusé";
        }
    }
    return "stop";
}