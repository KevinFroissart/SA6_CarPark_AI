#include "../headers/Voiture.hpp"
#include "../headers/Parking.hpp"
#include "../headers/ToolBox.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
using namespace std;

void startServer(Parking * P){
    if(!P->demarerServer()) cout << "Le parking ne parviens pas à démarrer le serveur" << endl;
}

void connexionServer(Voiture * v, int port, int id){
    if(!v->connexionServer(port, id)) cout << "La voiture ne parviens pas à se connecter au serveur" << endl;
}

int main (void){

    int nb_parking = 3;
    vector<Parking *> listeParking;
    vector<thread *> listeThreadParking;

    for(int i = 0; i < nb_parking; i++){
        listeParking.push_back(new Parking(i+1, "parking.csv"));  
        listeThreadParking.push_back(new thread(startServer, listeParking[i]));
        listeThreadParking[i]->detach();
    }

    sleep(4);

    int nb_voiture = 30;
    vector<Voiture *> listeVoiture;
    vector<Voiture *> listeVoitureTmp;

    for(int i = 0; i < nb_voiture; i++){
        listeVoitureTmp.push_back(new Voiture(i + 1, "voitures.csv"));
    }

    //Ajouter des voitures de manière aléatoire dans notre liste
    while(listeVoiture.size() != (unsigned int) nb_voiture){
        srand(time(NULL));
        int voitureRand = rand() % (int) listeVoitureTmp.size();
        
        listeVoiture.push_back(new Voiture(listeVoitureTmp[voitureRand]->getID(), "voitures.csv"));
        listeVoitureTmp.erase(listeVoitureTmp.begin() + voitureRand);
    }

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 1000), "SA6 Parking Manager");

    sf::Event event;

    while(window.isOpen()){
        while(window.pollEvent(event)){

            switch (event.type){
                case sf::Event::Closed: 
                    window.close(); 
                    break;
                case sf::Event::KeyPressed :
                    if(event.key.code == sf::Keyboard::Q) window.close();
                    break;
                default:
                    break;
            }
        }
        /*
        //Creer les threads pour chaque voitures
        for(int i = 0; i < nb_voiture; i++){
            for(int j = 0; j < nb_parking && listeVoiture[i]->rechercheParking; j++){
                thread * tmp = new thread(connexionServer, listeVoiture[i], listeParking[j]->getPort(), listeParking[j]->getId());
                tmp->join();
                delete tmp;
            }
            cout << (listeVoiture[i]->rechercheParking ? "La voiture n'as pas trouvé de parking" : "La voiture a trouvé un parking");
            cout << endl;
        }

        for(int i = 0; i < nb_parking; i++){
            delete listeThreadParking[i];
            delete listeParking[i];
        }      
        for(Voiture* voiture : listeVoiture){
            delete voiture;
        }*/

        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
            return EXIT_FAILURE;
        
        window.clear();

        for(int i = 0; i < nb_parking; i++){
            sf::Text text("Parking " + to_string(i+1), font, 50);
            int y = i*50;
            text.move(0.f, y);
            
            int length = 300;
            int width = 50;
            float progress_scale = length/stoi(listeParking[i]->getCapaciteTotale());

            sf::RectangleShape ProgressBackground;
            ProgressBackground.setFillColor(sf::Color::White);
            ProgressBackground.setOutlineThickness(2);
            ProgressBackground.setOutlineColor(sf::Color::Red);
            ProgressBackground.setSize(sf::Vector2f(length, width));
            ProgressBackground.move(300.f, y);

            sf::RectangleShape ProgressBar;
            ProgressBar.setFillColor(sf::Color::Red);
            ProgressBar.setOutlineThickness(2);
            ProgressBar.setOutlineColor(sf::Color::Red);
            ProgressBar.setSize(sf::Vector2f(stoi(listeParking[i]->getRemplissage()) * progress_scale, width));
            ProgressBar.move(300.f, y);

            window.draw(ProgressBackground);
            window.draw(ProgressBar);
            window.draw(text);  
        }

        window.display();        
    }

    return 0;
}