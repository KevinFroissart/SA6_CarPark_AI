#include "../headers/Parking.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/ServerParking.hpp"
#include <math.h>

/**
 * @brief Construct a new Parking:: Parking object
 * @param id 
 * @param defaultPrice 
 * @param capacite_max 
 * @param cheminFichier 
 */
Parking::Parking(int id, float defaultPrice, int capacite_max, string cheminFichier) : filePath(cheminFichier)
{
    s_parkingData[1] = defaultPrice;
    s_parkingData[0] = id;
    s_parkingData[2] = "0";
    s_parkingData[3] = capacite_max;
    ofstream File(filePath);
    if (File.is_open())
    {
        File << s_parkingData[0] << "," << s_parkingData[1] << "," << s_parkingData[2] << "," << s_parkingData[3] << "\n";
        File.close();
    }
    else
        throw runtime_error("Could not open file");
}

/**
 * @brief Construct a new Parking:: Parking object
 * @param id 
 * @param cheminFichier 
 */
Parking::Parking(int id, string cheminFichier) : filePath(cheminFichier)
{
    string input = tb::CSVReader(filePath, id);
    stringstream input_stringstream(input);

    getline(input_stringstream, s_parkingData[0], ','); //id
    getline(input_stringstream, s_parkingData[1], ','); //prix
    getline(input_stringstream, s_parkingData[2], ','); //remplissage
    getline(input_stringstream, s_parkingData[3], ','); //capacite
    getline(input_stringstream, s_parkingData[4], ','); //port
    logPath = "CSV/Parking/parking" + s_parkingData[0] + "Log.csv";
    fstream existe(logPath);
    if (!existe.is_open())
    {
        ofstream createLog(logPath);
        createLog.close();
    }
    else
        existe.close();
}

/**
 * @brief Destroy the Parking:: Parking object
 */
Parking::~Parking()
{
    Sockets::Release();
}

/**
 * @brief Get the parking id
 * @return int the parking's id
 */
int Parking::getId()
{
    return stoi(s_parkingData[0]);
}

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool Parking::EstRempli()
{
    return (s_parkingData[2] == s_parkingData[3]);
}

/**
 * @brief method that return the port of the server.
 * @return the port of the server.
 */
int Parking::getPort()
{
    return stoi(s_parkingData[4]);
}

/**
 * @brief 
 * @param tab 
 * @return float 
 */
float Parking::calcul_prix(vector<string> tab)
{
    vector<float> tab_facteurs;

    idVoiture.push_back(tab[0]);
    tab_facteurs.push_back(stof(tab[1])); //facteur durée

    float nb_heures = tab_facteurs[0];
    float prix = stof(s_parkingData[1]);

    //on passe les facteurs dans le vector courant. Et les normalisons (entre 0 et 1)
    tab_facteurs.push_back(1 - 0.25 * stof(tab[2]));                       //Facteur handicap
    tab_facteurs.push_back(1 - 0.25 * stof(tab[3]));                       //facteur age (jeune, adulte, vieux)
    tab_facteurs.push_back(1 - 0.25 * stof(tab[4]));                       //facteur statut social
    tab_facteurs.push_back(1 - 0.25 * tb::readLog(stof(tab[0]), logPath)); //client habitué?

    float somme_facteur = 0;
    for (unsigned int i = 1; i < tab_facteurs.size(); i++)
    {
        somme_facteur += tab_facteurs[i];
    }
    //la somme des scores de tous les facteurs. Compris entre 0 (aucune bonus) et nb_facteurs (tous les bonus à 1) donc

    somme_facteur /= (tab_facteurs.size() - 1); //la moyenne des facteurs

    prix *= somme_facteur;
    prix *= 0.7 * nb_heures + 0.3 * (float)log(nb_heures);
    prix *= 1 + 0.75 * (stof(s_parkingData[2]) / stof(s_parkingData[3]));

    return s_prix = prix;
}

/**
 * @brief 

 * @return true 
 * @return false 
 */
bool Parking::demarerServer()
{
    if (!Sockets::Start())
    {
        std::cout << "Erreur initialisation sockets : " << Sockets::GetError() << std::endl;
        return -1;
    }
    //int port;
    std::cout << "Port du serveur > " + s_parkingData[4] << endl;
    //std::cin >> port;
    if (!ServerP::Server(stoi(s_parkingData[4]), this)) // on envoie l'instance de notre parking au serveur pour pouvoir utiliser la méthode protocole depuis le ServerParking
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
 * @param message 
 * @return string 
 */
string Parking::protocoleCommunication(string message, int etape)
{
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

    // Vérifie si il reste de la place dans le parking, si non on arrete l'échange, si oui on continu
    if (etape == 1)
        return EstRempli() ? "Non" : "Oui";

    if (etape == 2)
    {
        s_infoVoiture = message;
        calcul_prix(tb::StringToTab(message, ','));

        vector<string> tmpTab = tb::StringToTab(message, ',');
        if (discussionVoiture.find(tmpTab[0]) == discussionVoiture.end())
        {
            discussionVoiture.insert(pair<string, string>(tmpTab[0], ""));
        }
        itr = discussionVoiture.find(tmpTab[0]);
        //////////////////
        id_voiture = "Voiture " + tmpTab[0] + ": ";
        id_parking = "Parking " + to_string(getId()) + ": ";
        itr->second += id_voiture + "Est-ce que vous avez de la place ?\n" + id_parking + "Oui\n";
        itr->second += id_voiture + "Tres bien, voici une trame contenant mes informations <" + message + ">\n";
        itr->second += id_parking + "C'est recu, je peux vous obtenir une place pour " + to_string(s_prix) + "e.\n";
        return to_string(s_prix);
    }
    if (etape == 3)
    {
        //Si la voiture accepte ce prix alors on lui reserve une place et on lui indique que c'est bon
        if (message == "Accepte")
        {
            itr->second += id_voiture + "J'accepte !\n";
            return ajouterVoiture();
        }
        else
        { //Si la voiture n'accepte pas alors elle nous renvoie son prix
            itr->second += id_voiture + "Desole, ca ne rentre pas dans mon budget, voici mon offre: " + message + "e\n";
            prix_demande = stof(message);
            if (prix_demande > (0.75 * s_prix))
            {
                itr->second += id_parking + "J'accepte !\n";

                return ajouterVoiture();
            }
            itr->second += id_parking + "Desole mais je me dois de refuser !\n";
            return "Refuse";
        }
    }
    if (etape == 4)
    {
        // Le parking a refusé mais la voiture négocie
        if (message.find("handicap") != string::npos)
        {
            itr->second += id_voiture + message + "\n";
            if (tb::StringToTab(s_infoVoiture, ',')[2] == "1")
            {
                itr->second += id_parking + "Je comprends, j'accepte votre precedente offre.\n";
                return ajouterVoiture();
            }
            else
            {
                itr->second += id_parking + "Desole mais les informations que vous m'avez communique me disent le contraire.\n";
                return "Refuse";
            }
        }
        if (message.find("en semaine"))
        {
            itr->second += id_voiture + message + "\n";
            if ((aTime->tm_hour > 7 && aTime->tm_hour < 9) ||
                (aTime->tm_hour > 17 && aTime->tm_hour < 18))
            {
                itr->second += id_parking + "Oui mais nous sommes en pleine heure de pointe !\n";
                return "Refuse";
            }
            else if (prix_demande > (0.65 * s_prix))
            {
                itr->second += id_parking + "Je vous l'accorde.\n";
                return ajouterVoiture();
            }
            else
            {
                itr->second += id_parking + "C'est vrai mais votre prix est toujours trop haut.\n";
                return "Refuse";
            }
        }
        if (message.find("heure"))
        {
            itr->second += id_voiture + message + "\n";
            if (aTime->tm_wday > 5)
            {
                itr->second += id_parking + "Oui mais nous sommes le week end !\n";
                return "Refuse";
            }
            else if (prix_demande > (0.65 * s_prix))
            {
                itr->second += id_parking + "Je vous l'accorde.\n";
                return ajouterVoiture();
            }
            else
            {
                itr->second += id_parking + "C'est vrai mais votre prix est toujours trop haut.\n";
                return "Refuse";
            }
        }
    }
    if (etape == 5)
    {
        itr->second += id_voiture + message + "\n";
        if (message.find("regulie"))
        {
            if (tb::readLog(getId(), logPath) == 2)
            {
                if (prix_demande < (s_prix * 0.75))
                {
                    itr->second += id_parking + "Vous etes un client tres fidele mais il nous ait impossible d'acceder a votre demande.\n";
                    itr->second += id_parking + "Voici une reduction pour vous remercier de votre fidelite: " + to_string(s_prix * 0.75) + "\n";
                    return to_string(s_prix * 0.75);
                }
                else
                {
                    itr->second += id_parking + "C'est vrai, merci de votre fidelite.\n";
                    return ajouterVoiture();
                }
            }
            else if (tb::readLog(getId(), logPath) == 1)
            {
                itr->second += id_parking + "Vous venez souvent mais pas assez pour un tel rabais.\n";
                itr->second += id_parking + "Voici une reduction pour vous remercier de votre fidelite: " + to_string(s_prix * 0.80) + "\n";
                return to_string(s_prix * 0.80);
            }
            else
            {
                itr->second += id_parking + "Vous n'etes presque jamais venu..\n";
                return "Refuse";
            }
        }
    }
    if (etape == 6)
    {
        if (message == "Accepte")
        {
            itr->second += id_voiture + "J'accepte votre offre.\n";
            return ajouterVoiture();
        }
        else
            itr->second += id_voiture + message + "\n";
    }
    return "stop";
}

/**
 * @brief When a car is added, the whole process is done here.
 * @return a message fot the car
 */
string Parking::ajouterVoiture()
{
    s_parkingData[2] = to_string(stoi(s_parkingData[2]) + 1);
    tb::CSVWriterParkLogs("CSV/Parking/", "parking" + s_parkingData[0] + "Log.csv", idVoiture[0]);
    idVoiture.erase(idVoiture.begin());
    itr->second += id_parking + "Bienvenue dans mon parking\n";
    s_caisse += s_prix;
    return "OK, place reservée";
}

/**
 * @brief return the amount the Parking earned by renting slots.
 * @return float 
 */
float Parking::caisseTotal()
{
    return s_caisse;
}

/**
 * @brief return the total capacity of the Parking.
 * @return string 
 */
string Parking::getCapaciteTotale()
{
    return s_parkingData[3];
}

/**
 * @brief return the amount of slots already filled.
 * 
 * @return string 
 */
string Parking::getRemplissage()
{
    return s_parkingData[2];
}