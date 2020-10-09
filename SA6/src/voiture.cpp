#include "../headers/voiture.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/Sockets.hpp"
#include <sstream>
#include <math.h>

ToolBox tb;    

/**
 * Voiture Constructor, extracts information from a CSV file.
 *
 * @param id the id number of the car.
 * @param filePath path of the CSV file.
 * @return the object Voiture.
 */
Voiture::Voiture(int id, string filePath) : v_id(id), v_path(filePath){
    string input = tb.CSVReader(v_path, v_id);
    stringstream input_stringstream(input);

    getline(input_stringstream, v_name, ',');
    getline(input_stringstream, v_marque, ',');
    getline(input_stringstream, v_statut, ',');
    getline(input_stringstream, v_handicap, ',');
    getline(input_stringstream, v_age, ',');
    getline(input_stringstream, v_heure, ',');
    v_prixBase = 2;

    initTab();
}

/**
 * Voiture Constructor
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
Voiture::Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure) : 
v_id(id), v_name(name), v_marque(marque), v_statut(statut), v_handicap(handicap), v_age(age), v_heure(heure){
    v_prixBase = 2;
    initTab();
}

/**
 * Voiture Destructor.
 */
Voiture::~Voiture(){
    //destructeur
}

/**
 * Prints the car informations.
 */
void Voiture::printData(){
    cout<<"id: "<<v_id<<" | "<<v_name<<" | Marque: "<<v_marque <<" | Statut: "<<v_statut<<" | Handicap: "<<v_handicap<<" | age: "<<v_age<<" | heure: "<<v_heure<<endl;
    tb.floatTabToString(v_tab, ',');
}

/**
 * Returns a tab of floats designed for socket communication
 * and Parking management.
 *
 * @return float tab.
 */
vector<float> Voiture::initTab(){
    v_tab.push_back(v_id);
    v_tab.push_back(stoi(v_heure));
    v_tab.push_back(v_handicap == "oui" ? 1 : 0); // si Vrai = 1 sinon = 0
    v_tab.push_back(stoi(v_age) < 60 ? stoi(v_age) < 25 ? 1 : 0 : 2); //age > 60 = 2 | age < 25 = 1 sinon 0
    v_tab.push_back(v_statut == "salarié" ? 1 : v_statut == " patron" ? 0 : 2); //salarié = 1 | patron = 2 sinon 0
    return v_tab;
} 

/**
 * Method that calculates the park price the
 * car owner wants to pay.
 *
 * This method uses different data such as the owner status,
 * if he has a handicap, his age and the time he wants to stay.
 * 
 * @return prix, the fiual price.
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
    cout<<"prix 1 = "<<prix<<endl;

    prix *= ((somme_facteur / (tab_facteurs.size()-1))        //moyenne des facteurs (compris entre 0 et 2) sauf la durée
                * (nb_heures*0.7 + 0.3*(float)log(nb_heures)));   // fois le nombre d'heures (et un logarithme);
    cout<<"prix après réduction = "<<prix<<endl;
    return prix;
}

/**
 * Method used to connect the car with a specific Parking using sockets.
 *
 * @param port the port of the Parking's server.
 * @return false if the Voiture can't connect, true otherwise.
 */
bool Voiture::connexionServer(int port)
{
    v_etape = 1; // à chaque connexion au server on remet l'étape du protocole à 1
	if(!Sockets::Start())
	{
		cout << "Error starting sockets : " << Sockets::GetError() << std::endl;
		return false;
	}
	TCPSocket client;
	if(!client.Connect("127.0.0.1", port)){
		cout << "Impossible de se connecter au serveur [127.0.0.1:" << port << "] : " << Sockets::GetError() << endl;
        return false;
    }
	else
	{
		cout << v_name << " est connectée!" << endl;
		communicateWithParking(client, ""); //on démarre la conversation avec le serveur
	}
	Sockets::Release();
	return true;
}

bool Voiture::communicateWithParking(TCPSocket client, string replyServer) { 
    string phrase = protocoleCommunication(replyServer);

    if(phrase == "stop"){ //Si le protocole nous renvoie stop, on coupe la communication avec le parking
        cout << "Communication terminée";
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
			cout << "Reponse du serveur : " << reply << endl;
            communicateWithParking(client, reply); //on fait de la récurrence pour faire tourner le protocole
		}
	}
    return true;    
}

string Voiture::protocoleCommunication(string message){
    string res = "stop"; //si on est en dehors des étapes du protocole il y une erreur quelque part, on stop la communication
    if(v_etape == 1){
        //étape 1, La voiture et le parking n'ont encore jamais communiqué, je demande au parking s'il a de la place
        v_etape++;
        return "Est-ce que vous avez de la place ?";
    }
    if(v_etape == 2){
        //étape 2, le parking me répond, s'il à de la place je lui envoie mes informations personnelles, sinon j'arrête la communication en envoyant "stop"
        if(message == "Non")
            return "stop";
        else {
            v_etape++;
            return tb.floatTabToString(v_tab, ',');
        }
    }
    if(message == ""){
        v_etape++;
        return res; //étape 3
    }
    if(message == ""){
        v_etape++;
        return res; //étape 4
    }
    if(message == ""){
        v_etape++;
        return res; //étape 5
    }
    return res;
}