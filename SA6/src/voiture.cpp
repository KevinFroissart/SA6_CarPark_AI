#include "../headers/Voiture.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/Sockets.hpp"
#include <math.h>

/**
 * @brief Voiture Constructor, extracts information from a CSV file.
 *
 * @param id the id number of the car.
 * @param filePath path of the CSV file.
 * @return the object Voiture.
 */
Voiture::Voiture(int id, string filePath) : v_id(id), v_path(filePath){
    string input = tb::CSVReader(v_path, v_id);
    stringstream input_stringstream(input);

    getline(input_stringstream, v_voitureData[0], ','); //name
    getline(input_stringstream, v_voitureData[1], ','); //marque
    getline(input_stringstream, v_voitureData[2], ','); //statut
    getline(input_stringstream, v_voitureData[3], ','); //handicap
    getline(input_stringstream, v_voitureData[4], ','); //age
    getline(input_stringstream, v_voitureData[5], ','); //heure
    v_prixBase = 2;
    rechercheParking = true;

    logPath = "CSV/Voiture/voiture" + to_string(v_id) + "Log.csv";
    fstream existe(logPath);
    if(!existe.is_open()){
        ofstream createLog(logPath);
        createLog.close();
    } else existe.close();

    initTab();
}

/**
 * @brief Voiture Constructor
 *
 * @param id the id number of the car.
 * @param name the name of the car.
 * @param marque the brand of the car.
 * @param statut the car owner's status.
 * @param handicap if the owner has a handicap.
 * @param age the age of the car owner.
 * @param heure the number of hour the owner is willing to park.
 * @return the object Voiture.
 */
Voiture::Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure) {
    v_id = id;
    v_voitureData[0] = name;
    v_voitureData[1] = marque;
    v_voitureData[2] = statut;
    v_voitureData[3] = handicap;
    v_voitureData[4] = age;
    v_voitureData[5] = heure;
    v_prixBase = 2;
    rechercheParking = true;
    
    logPath = "CSV/Voiture/voiture" + to_string(v_id) + "Log.csv";
    fstream existe(logPath);
    if(!existe.is_open()){
        ofstream createLog(logPath);
        createLog.close();
    } else existe.close();

    initTab();
}

/**
 * @brief Voiture Destructor.
 */
Voiture::~Voiture(){
    //destructeur
}

/**
 * @brief Returns a tab of floats designed for socket communication
 * and Parking management.
 *
 * @return float tab.
 */
vector<float> Voiture::initTab(){
    v_tab.push_back(v_id);
    v_tab.push_back(stoi(v_voitureData[5]));
    v_tab.push_back(v_voitureData[3] == "oui" ? 1 : 0); // si Vrai = 1 sinon = 0
    v_tab.push_back(stoi(v_voitureData[4]) < 60 ? stoi(v_voitureData[4]) < 25 ? 1 : 0 : 2); //age > 60 = 2 | age < 25 = 1 sinon 0
    v_tab.push_back(v_voitureData[2] == "salarié" ? 1 : v_voitureData[2] == " patron" ? 0 : 2); //salarié = 1 | patron = 2 sinon 0
    return v_tab;
} 

/**
 * @brief methoid that returns the ID of the Voiture
 * 
 * @return int the ID 
 */
int Voiture::getID(){
    return v_id;
}

/**
 * @brief Method that calculates the park price the
 * car owner wants to pay.
 *
 * This method uses different data such as the owner status,
 * if he has a handicap, his age and the time he wants to stay.
 * 
 * @return prix, the calculated price.
 */
float Voiture::calcul_prix(){
    vector <float> tab_facteurs;
    float prix = (float) v_prixBase;
    // la 1ere case du vector est la durée
    tab_facteurs.push_back( v_tab[1]);              //facteur durée
    float nb_heures = tab_facteurs[0]; 

    tab_facteurs.push_back(1 - 0.25 * v_tab[2]);    //Facteur handicap
    tab_facteurs.push_back(1 - 0.25 * v_tab[3]);    //facteur age (jeune, adulte, vieux)
    tab_facteurs.push_back(1 - 0.25 * v_tab[4]);    //facteur statut social

    float somme_facteur = 0;
    for(unsigned int i = 1; i<tab_facteurs.size(); i++){
        somme_facteur += tab_facteurs[i];
    }

    prix *= 0.90*((somme_facteur / (tab_facteurs.size()-1))        //moyenne des facteurs (compris entre 0 et 2) sauf la durée
                * (nb_heures*0.7 + 0.3*(float)log(nb_heures)));   // fois le nombre d'heures (et un logarithme);
    return prix;
}

/**
 * @brief Method used to connect the car with a specific Parking using sockets.
 *
 * @param port the port of the Parking's server.
 * @param id the parking's id.
 * @return false if the Voiture can't connect, true otherwise.
 */
bool Voiture::connexionServer(int port, int id)
{
    idParking = id;
    v_etape = 1; // à chaque connexion au server on remet l'étape du protocole à 1
	if(!Sockets::Start())
	{
		cout << "Error starting sockets : " << Sockets::GetError() << std::endl;
		return false;
	}
	SocketVoiture client;
	if(!client.Connect("127.0.0.1", port)){
		cout << "Impossible de se connecter au serveur [127.0.0.1:" << port << "] : " << Sockets::GetError() << endl;
        return false;
    }
	else
	{
		//cout << v_voitureData[0] << " est connectée!" << endl;
		communicateWithParking(client, ""); //on démarre la conversation avec le serveur
	}
	Sockets::Release();
	return true;
}


/**
 * @brief Method used to send a string to the Parking using sockets
 *
 * @param client the socket used to send the message.
 * @param replyServer the reply of the server, used for recursive purposes
 * @return false there is there is any error or if the communication is over, true otherwise.
 */
bool Voiture::communicateWithParking(SocketVoiture client, string replyServer) { 
    string phrase = protocoleCommunication(replyServer);

    if(phrase == "stop"){ //Si le protocole nous renvoie stop, on coupe la communication avec le parking
        //cout << "Communication terminée" << endl << endl;
        return false;
    }
	if(client.Send(phrase.c_str(), phrase.length()) == SOCKET_ERROR){ //Ici on envoie le message au parking et on vérifie s'il n'y a pas d'erreur
		cout << "Erreur envoi : " << Sockets::GetError() << endl;
        return false;
    }
	else //Si le message a bien été envoyé on récupère la réponse ici
	{
		char buffer[512] = {0};
		int len = client.Receive(buffer, 512);
		if(len == SOCKET_ERROR)
			cout << "Erreur reception : " << Sockets::GetError() << endl;
		else
		{
			string reply(buffer, len);
            communicateWithParking(client, reply); //on fait de la récurrence pour faire tourner le protocole
		}
	}
    return true;    
} 

/**
 * @brief Method used to chose which message the Voiture has to send depending
 * on the state of the Protocol and the message recieved.
 *
 * @param message the message recieved from the server.
 * @return the string that will be send to the server.
 */
string Voiture::protocoleCommunication(string message){
    if(v_etape == 1){
        //étape 1, La voiture et le parking n'ont encore jamais communiqué, je demande au parking s'il a de la place
        v_etape++;
        return "Est-ce que vous avez de la place ?";
    }

    if(v_etape == 2){
        //étape 2, le parking me répond, s'il à de la place je lui envoie mes informations personnelles, sinon j'arrête la communication en envoyant "stop"
        if(message == "Non") return "stop";
        else {
            v_etape++;
            return tb::floatTabToString(v_tab, ',');
        }
    }

    if(v_etape == 3){
        if(stoi(message) <= v_prixBase){ // Si le prix renvoyé par le parking est inférieur ou égal au prix voulu par la voiture alors elle accepte
            v_etape++;
            tb::CSVWriterParkLogs("CSV/Voiture/", "voiture" + to_string(v_id) + "Log.csv", to_string(idParking));
            return "Accepte";
        }
        else { //Sinon on refuse pour tenter la négociation en proposant un prix
            int prix = calcul_prix();
            v_etape++;
            return to_string(prix);
        }
    }

    if (v_etape == 4) {
        if(message == "Refusé") return "stop";

        rechercheParking = false;
        return "stop";
    }
    return "stop";
}