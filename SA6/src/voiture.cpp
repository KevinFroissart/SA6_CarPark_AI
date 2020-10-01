#include "../headers/voiture.h"
#include "../headers/CSVManager.h"
#include "../headers/Sockets.h"
#include "../headers/TCPSocket.h"
#include <sstream>
#include <math.h>

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
    v_prixBase = 2;

    initTab();
}

Voiture::Voiture(int id, string name, string marque, string statut, string handicap, string age, string heure) : 
v_id(id), v_name(name), v_marque(marque), v_statut(statut), v_handicap(handicap), v_age(age), v_heure(heure){
    v_prixBase = 2;
    initTab();
}

Voiture::~Voiture(){
    //destructeur
}

void Voiture::printData(){
    cout<<"id: "<<v_id<<" | "<<v_name<<" | Marque: "<<v_marque <<" | Statut: "<<v_statut<<" | Handicap: "<<v_handicap<<" | age: "<<v_age<<" | heure: "<<v_heure<<endl;
    tabToString(v_tab, ',');
}

vector<float> Voiture::initTab(){
    v_tab.push_back(v_id);
    v_tab.push_back(stoi(v_heure));
    v_tab.push_back(v_handicap == "oui" ? 1 : 0); // si Vrai = 1 sinon = 0
    v_tab.push_back(stoi(v_age) < 60 ? stoi(v_age) < 25 ? 1 : 0 : 2); //age > 60 = 2 | age < 25 = 1 sinon 0
    v_tab.push_back(v_statut == "salarié" ? 1 : v_statut == " patron" ? 0 : 2); //salarié = 1 | patron = 2 sinon 0
    return v_tab;
} 

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

bool Voiture::communicateServer()
{
	if(!Sockets::Start())
	{
		cout << "Error starting sockets : " << Sockets::GetError() << std::endl;
		return false;
	}
	TCPSocket client;
	int port = 8080;
	if(!client.Connect("127.0.0.1", port))
		cout << "Impossible de se connecter au serveur [127.0.0.1:" << port << "] : " << Sockets::GetError() << endl;
	else
	{
		cin.ignore();
		cout << "Connecte!" << endl;
		string phrase = tabToString(v_tab, ',');
		getline(cin, phrase);
		if(client.Send(phrase.c_str(), phrase.length()) == SOCKET_ERROR)
			cout << "Erreur envoi : " << Sockets::GetError() << endl;
		else
		{
			char buffer[512] = {0};
			int len = client.Receive(buffer, 512);
			if(len == SOCKET_ERROR)
				cout << "Erreur reception : " << Sockets::GetError() << endl;
			else
			{
				string reply(buffer, len);
				cout << "Reponse du serveur : " << reply << endl;
			}
		}
	}
	Sockets::Release();
	return true;
}

string Voiture::tabToString(vector<float> tab, char delimiter) {
    string res = to_string((int) tab[0]);
    if(tab.size() > 1) {
        for(unsigned int i = 1; i < tab.size(); i++){
            res += delimiter + to_string((int) tab[i]);
        }
    }
    cout << res << endl;
    return res;
}