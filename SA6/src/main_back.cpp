#include "../headers/main_back.hpp"
#include <algorithm>
#include <random>

using namespace std;

/**
 * @brief run the server
 * 
 * @param P 
 */
void startServer(Parking *P)
{
    if (!P->demarerServer())
        cout << "Le parking ne parviens pas à démarrer le serveur" << endl;
}

/**
 * @brief connect a Voiture to a Parking
 * 
 * @param v 
 * @param port 
 * @param id 
 */
void connexionServer(Voiture *v, int port, int id)
{
    if (!v->connexionServer(port, id))
        cout << "La voiture ne parviens pas à se connecter au serveur" << endl;
}

/**
 * @brief Construct a new Main_back::Main_back object
 * initialise Parking, Voiture and Thread lists.
 * Voitures are stored randomly.
 */
Main_back::Main_back()
{

    m_nbParking = 3;
    m_nbVoiture = 30;

    vector<Parking *> listeParking;
    vector<thread *> listeThreadParking;

    vector<Voiture *> listeVoiture;
    vector<Voiture *> listeVoitureTmp;

    for (int i = 0; i < m_nbParking; i++)
    {
        listeParking.push_back(new Parking(i + 1, "parking.csv"));
        listeThreadParking.push_back(new thread(startServer, listeParking[i]));
        listeThreadParking[i]->detach();
    }

    for (int i = 0; i < m_nbVoiture; i++)
    {
        listeVoitureTmp.push_back(new Voiture(i + 1, "voitures.csv"));
    }

    while (listeVoiture.size() != (unsigned int)m_nbVoiture)
    {
        srand(time(NULL));
        int voitureRand = rand() % (int)listeVoitureTmp.size();

        listeVoiture.push_back(new Voiture(listeVoitureTmp[voitureRand]->getID(), "voitures.csv"));
        listeVoitureTmp.erase(listeVoitureTmp.begin() + voitureRand);
    }

    m_listeParking = listeParking;
    m_listeParking_shuffle = listeParking;
    m_listeThreadParking = listeThreadParking;
    m_listeVoiture = listeVoiture;
    m_listeVoitureTmp = listeVoitureTmp;
}

/**
 * @brief Destroy the Main_back::Main_back object
 * Destroys every Parking Objects and Threads previously created.
 */
Main_back::~Main_back()
{
    for (int i = 0; i < m_nbParking; i++)
    {
        delete m_listeThreadParking[i];
        delete m_listeParking[i];
    }
}

/**
 * @brief This is where the magic happens!
 * The whole process is done here hence the name of the method.
 * Each Voiture seeks a Parking and they argue prices while looking for a slot.
 * the 'sleep(4)' is necessary in order to let the Parkings servers start.
 * @return int 
 */
int Main_back::process()
{

    sleep(4);

    for (int i = 0; i < m_nbVoiture; i++)
    {
        srand(unsigned(time(NULL)));
        std::random_shuffle(m_listeParking_shuffle.begin(), m_listeParking_shuffle.end());
        for (int j = 0; j < m_nbParking && m_listeVoiture[i]->rechercheParking; j++)
        {
            thread *tmp = new thread(connexionServer, m_listeVoiture[i], m_listeParking_shuffle[j]->getPort(), m_listeParking_shuffle[j]->getId());
            tmp->join();
            usleep(700);

            map<string, string>::iterator itr;
            if ((itr = m_listeParking_shuffle[j]->discussionVoiture.find(to_string(m_listeVoiture[i]->getID()))) != m_listeParking_shuffle[j]->discussionVoiture.end())
            {
                conversation[m_listeParking_shuffle[j]->getId()].insert(make_pair(m_listeVoiture[i]->getID(), itr->second));
                map<int, string>::iterator itr_tmp1;
                map<int, map<int, string>>::iterator itr_tmp2;
                if ((itr_tmp1 = conversation[m_listeParking_shuffle[j]->getId()].find(m_listeVoiture[i]->getID())) != conversation[m_listeParking_shuffle[j]->getId()].end())
                {
                    cout << itr_tmp1->second << endl;
                }
            }
            delete tmp;
        }
    }

    for (Voiture *voiture : m_listeVoiture)
    {
        delete voiture;
    }

    return 0;
}