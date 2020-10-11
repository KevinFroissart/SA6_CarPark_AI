#include "../headers/parking.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/ServerParking.hpp"
#include <sstream>
#include <vector>
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
    s_remplissage = '0';
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
 * 
 */
Parking::~Parking(){
//destructeur
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
 * @brief 
 * 
 * @param tab 
 * @return float 
 */
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
    //cout<<"prix après réduction = "<<prix<<endl;
    return prix;
}

/**
 * @brief 
 * 
 * @param tab 
 * @return float 
 */
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

/**
 * @brief 
 * 
 * @param prix_propose 
 * @param tab 
 * @return float 
 */
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

//on fait appel au protocole directement dans la classe ServerPaking
/**
 * @brief 
 * 
 * @param message 
 * @return string 
 */
string Parking::protocoleCommunication(string message){
    string res = "";
    if(message == "Est-ce que vous avez de la place ?"){
        if(s_remplissage >= s_capacite)
            return "Non";
        else
            return "Oui";
    }
    if(message == ""){
        return res;
    }
    if(message == ""){
        return res;
    }
    if(message == ""){
        return res;
    }
    if(message == ""){
        return res;
    }
    if(message == ""){
        return res;
    }
    return res;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Parking::demarerServer()
{
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
	return 0;
}