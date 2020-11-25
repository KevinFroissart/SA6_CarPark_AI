#include "../headers/Voiture.hpp"
#include "../headers/Parking.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/main_back.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
using namespace std;

void back_end_process(Main_back * mb){
    mb->process();
}

int main (void){

    Main_back * main_b = new Main_back();

    thread * back_thread = new thread(back_end_process, main_b);
    back_thread->detach();

    int tab_capacite[main_b->m_nbParking];
    for(int i = 0; i < main_b->m_nbParking; i++){
        tab_capacite[i] = stoi(main_b->m_listeParking[i]->getCapaciteTotale());
    }

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 1000), "SA6 Parking Manager");

    sf::Event event;

    while(window.isOpen()){
        bool closed = false;
        while(window.pollEvent(event)){

            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    main_b->~Main_back(); 
                    closed = true;
                    break;
                case sf::Event::KeyPressed :
                    if(event.key.code == sf::Keyboard::Q){
                        window.close();  
                        main_b->~Main_back();
                        closed = true;
                    } 
                    break;
                default:
                    break;
            }
        }

        if(!closed){
            
            sf::Font font;
            if (!font.loadFromFile("arial.ttf"))
                return EXIT_FAILURE;
            
            window.clear();

            for(int i = 0; i < main_b->m_nbParking; i++){
                sf::Text text("Parking " + to_string(i+1), font, 50);
                int y = i*50;
                text.move(0.f, y);
                
                int length = 300;
                int width = 50;
                float progress_scale = length/tab_capacite[i];

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
                //cout << stoi(main_b->m_listeParking[i]->getRemplissage())  << " / " << length << endl;
                ProgressBar.setSize(sf::Vector2f(stoi(main_b->m_listeParking[i]->getRemplissage()) * progress_scale, width));
                ProgressBar.move(300.f, y);

                window.draw(ProgressBackground);
                window.draw(ProgressBar);
                window.draw(text);  
            }

            window.display(); 
        }       
    }

    return 0;
}