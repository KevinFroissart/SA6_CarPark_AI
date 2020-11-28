#include "../headers/main_back.hpp"

using namespace std;

void startServer(Parking * P){
    if(!P->demarerServer()) cout << "Le parking ne parviens pas à démarrer le serveur" << endl;
}

void connexionServer(Voiture * v, int port, int id){
    if(!v->connexionServer(port, id)) cout << "La voiture ne parviens pas à se connecter au serveur" << endl;
}

Main_back::Main_back(){

    m_nbParking = 3;
    m_nbVoiture = 30;

    vector<Parking *> listeParking;
    vector<thread *> listeThreadParking;

    vector<Voiture *> listeVoiture;
    vector<Voiture *> listeVoitureTmp;

    for(int i = 0; i < m_nbParking; i++){
        listeParking.push_back(new Parking(i+1, "parking.csv"));  
        listeThreadParking.push_back(new thread(startServer, listeParking[i]));
        listeThreadParking[i]->detach();
    }

    for(int i = 0; i < m_nbVoiture; i++){
        listeVoitureTmp.push_back(new Voiture(i + 1, "voitures.csv"));
    }

    //Ajouter des voitures de manière aléatoire dans notre liste
    while(listeVoiture.size() != (unsigned int) m_nbVoiture){
        srand(time(NULL));
        int voitureRand = rand() % (int) listeVoitureTmp.size();
        
        listeVoiture.push_back(new Voiture(listeVoitureTmp[voitureRand]->getID(), "voitures.csv"));
        listeVoitureTmp.erase(listeVoitureTmp.begin() + voitureRand);
    }


    m_listeParking = listeParking;
    m_listeThreadParking = listeThreadParking;
    m_listeVoiture = listeVoiture;
    m_listeVoitureTmp = listeVoitureTmp;
}

Main_back::~Main_back(){
    for(int i = 0; i < m_nbParking; i++){
        delete m_listeThreadParking[i];
        delete m_listeParking[i];
    }      
}

int Main_back::process (){

    sleep(4);

    //Creer les threads pour chaque voitures
    for(int i = 0; i < m_nbVoiture; i++){
        for(int j = 0; j < m_nbParking && m_listeVoiture[i]->rechercheParking; j++){
            thread * tmp = new thread(connexionServer, m_listeVoiture[i], m_listeParking[j]->getPort(), m_listeParking[j]->getId());
            tmp->join();
            usleep(700);

            map<string, string>::iterator itr;
            if((itr = m_listeParking[j]->discussionVoiture.find(to_string(i))) != m_listeParking[j]->discussionVoiture.end())
                conversation[j].insert(make_pair(i, itr->second));   
                
            map<int, float>::iterator itr2;
            if(caisseParking.find(j) == caisseParking.end()){
                caisseParking.insert(make_pair(j, m_listeParking[j]->caisseTotal()));
            } else {
                itr2 = caisseParking.find(j);
                itr2->second = m_listeParking[j]->caisseTotal();
            }
            delete tmp;
        }
        cout << (m_listeVoiture[i]->rechercheParking ? "La voiture n'as pas trouvé de parking" : "La voiture a trouvé un parking");
        cout << endl;
    }
    
    for(Voiture* voiture : m_listeVoiture){
        delete voiture;
    }
    
    return 0;
}