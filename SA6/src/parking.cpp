#include "../headers/parking.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/ServerParking.hpp"
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
    fstream existe("parking" + s_idParking + "Log.csv");
    if(!existe.is_open()){
        ofstream createLog("parking" + s_idParking + "Log.csv");
        createLog.close();
    } else existe.close();
    
}

/**
 * @brief Destroy the Parking:: Parking object
 */
Parking::~Parking(){
    Sockets::Release();
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
    vector<float> tab_facteurs;

    idVoiture.push_back(tab[0]);
    tab_facteurs.push_back(stof(tab[1])); //facteur durée

    float nb_heures = tab_facteurs[0]; 
    float prix = stof(s_prixBase);

    //on passe les facteurs dans le vector courant. Et les normalisons (entre 0 et 1)
    tab_facteurs.push_back(1 - 0.25 * stof(tab[2]));             //Facteur handicap
    tab_facteurs.push_back(1 - 0.25 * stof(tab[3]));            //facteur age (jeune, adulte, vieux)
    tab_facteurs.push_back(1 - 0.25 * stof(tab[4]));            //facteur statut social
    tab_facteurs.push_back(1 - 0.25 * readLog(stof(tab[0])));   //client habitué?

    float somme_facteur = 0;
    for(unsigned int i = 1; i<tab_facteurs.size(); i++){
        somme_facteur += tab_facteurs[i];
    }
    //la somme des scores de tous les facteurs. Compris entre 0 (aucune bonus) et nb_facteurs (tous les bonus à 1) donc

    somme_facteur /= (tab_facteurs.size() - 1); //la moyenne des facteurs
   
    prix *= somme_facteur;
    prix *= 0.7 * nb_heures + 0.3 * (float) log(nb_heures);
    prix *= 1 + 0.75 * (stof(s_remplissage) / stof(s_capacite));

    return s_prix = prix;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Parking::demarerServer(){
	if(!Sockets::Start())
	{
		std::cout << "Erreur initialisation sockets : " << Sockets::GetError() << std::endl;
		return -1;
	}
	//int port;
	std::cout << "Port du serveur > " + s_port << endl;
	//std::cin >> port;
	if (!ServerP::Server(stoi(s_port), this)) // on envoie l'instance de notre parking au serveur pour pouvoir utiliser la méthode protocole depuis le ServerParking
	{
		std::cout << "Serveur termine avec l'erreur " << Sockets::GetError() << std::endl;
	}
	Sockets::Release();
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
        //Si la voiture accepte ce prix alors on lui reserve une place et on lui indique que c'est bon
        if(message == "Accepte")  return ajouterVoiture();
           
        else { //Si la voiture n'accepete pas alors elle nous renvoie son prix
            if(stof(message) > (0.65 * s_prix)) return ajouterVoiture();
            return "Refusé";
        }
    }
    return "stop";
}

/**
 * @brief When a car is added, the whole process is done here.
 * 
 * @return a message fot the car
 */
string Parking::ajouterVoiture() {
    ToolBox tb;
    s_remplissage = to_string(stoi(s_remplissage) + 1);
    tb.CSVWriterParkLogs("parking" + s_idParking + "Log.csv", idVoiture[0]);
    idVoiture.erase(idVoiture.begin());
    return "OK, place reservée";
}

/**
 * @brief collect the log of the car.
 * 
 * @return 0, 1, or 2 depending on how often the car visited the parking
 */

int Parking::readLog(int id){
    ToolBox tb;
    vector<string> string_passages = tb.StringToTab(tb.CSVReader("parking" + s_idParking + "Log.csv", id),',');
    int nb_passages = 0;
    if(string_passages.size() >= 1) string_passages[1];
    return nb_passages<5 ? 0 : nb_passages>10 ? 2 : 1;
}