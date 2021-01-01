#include "../headers/Voiture.hpp"
#include "../headers/Parking.hpp"
#include "../headers/ToolBox.hpp"
#include "../headers/main_back.hpp"
#include "../headers/dataWindow.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
using namespace std;

void back_end_process(Main_back *mb)
{
    mb->process();
}

void new_window(int idParking, Main_back *main_b)
{
    dataWindow *nw = new dataWindow(idParking, main_b);
    nw->newWindow();
}

/*bool CircleButton::collision(int x, int y) const{
    sf::Vector2f point(x,y);
    sf::FloatRect boundingBox = m_spriteButton.getGlobalBounds();
    return boundingBox.contains(point);
}

bool bouton(int x, int y, int tailleX, int tailleY){
    sf::Mouse::isButtonPressed(sf::Mouse::Left)
}*/

string round(float var)
{
    char *str = new char[40]; //uninitialised value ??..
    sprintf(str, "%.2f", var);
    sscanf(str, "%f", &var);
    string r = str;
    delete[] str;
    return r;
}

int main(void)
{

    Main_back *main_b = new Main_back();

    thread *back_thread = new thread(back_end_process, main_b);
    back_thread->detach();

    int tab_capacite[main_b->m_nbParking];
    for (int i = 0; i < main_b->m_nbParking; i++)
    {
        tab_capacite[i] = stoi(main_b->m_listeParking[i]->getCapaciteTotale());
    }

    vector<thread *> windows;

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, main_b->m_nbParking * 50 + 100), "SA6 Parking Manager");

    sf::Event event;

    while (window.isOpen())
    {
        bool closed = false;
        while (window.pollEvent(event))
        {

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                main_b->~Main_back();
                closed = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Q)
                {
                    window.close();
                    main_b->~Main_back();
                    closed = true;
                }
                break;
            default:
                break;
            }
        }

        if (!closed)
        {

            sf::Font font;
            if (!font.loadFromFile("arial.ttf"))
                return EXIT_FAILURE;

            window.clear(sf::Color(210, 210, 210, 255)); //gris

            for (int i = 0; i < main_b->m_nbParking; i++)
            {
                sf::Text text("Parking " + to_string(i + 1), font, 40);
                text.setFillColor(sf::Color::Black);
                int y = i * 50;
                text.move(0.f, y + 3);

                sf::Text label_progress(main_b->m_listeParking[i]->getRemplissage() + "/" + to_string(tab_capacite[i]), font, 40);
                label_progress.move(650.f, y + 3);
                label_progress.setFillColor(sf::Color::Black);

                map<int, float>::iterator itr;
                float caisse = 0;
                if ((itr = main_b->caisseParking.find(i)) != main_b->caisseParking.end())
                    caisse = itr->second;

                sf::Text label_caisse(round(caisse) + "e", font, 40);
                label_caisse.move(790.f, y + 3);
                label_caisse.setFillColor(sf::Color::Black);

                int length = 300;
                int width = 50;
                float progress_scale = length / tab_capacite[i];

                sf::RectangleShape ProgressBackground;
                ProgressBackground.setFillColor(sf::Color::White);
                ProgressBackground.setOutlineThickness(2);
                ProgressBackground.setOutlineColor(sf::Color::Black);
                ProgressBackground.setSize(sf::Vector2f(length, width));
                ProgressBackground.move(300.f, y);

                string conversation;

                for (map<int, string>::iterator itr_conv = main_b->conversation[i].begin(); itr_conv != main_b->conversation[i].end(); ++itr_conv)
                {
                    conversation += itr_conv->second + "\n";
                }

                sf::Text info_parking(conversation, font, 20);
                info_parking.setFillColor(sf::Color::Black);
                info_parking.move(700, 300);

                //cout << conversation << endl;

                sf::RectangleShape button;
                button.setOutlineColor(sf::Color::Black);
                button.setOutlineThickness(1);
                button.setSize(sf::Vector2f(length * 0.80, width));
                button.setFillColor(sf::Color::Transparent);
                button.move(0.f, y);
                if (sf::Mouse::getPosition(window).x > button.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (button.getGlobalBounds().left + button.getGlobalBounds().width) && sf::Mouse::getPosition(window).y > button.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (button.getGlobalBounds().top + button.getGlobalBounds().height))
                {
                    button.setOutlineColor(sf::Color::White);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        button.setFillColor(sf::Color::White);
                        window.draw(info_parking);
                        windows.push_back(new thread(new_window, i + 1, main_b));
                        windows[windows.size() - 1]->join();
                    }
                }

                sf::RectangleShape ProgressBar;
                ProgressBar.setFillColor(sf::Color::Red);
                ProgressBar.setOutlineThickness(2);
                ProgressBar.setOutlineColor(sf::Color::Black);
                ProgressBar.setSize(sf::Vector2f(stoi(main_b->m_listeParking[i]->getRemplissage()) * progress_scale, width));
                ProgressBar.move(300.f, y);

                window.draw(ProgressBackground);
                window.draw(ProgressBar);
                window.draw(button);
                window.draw(text);
                window.draw(label_progress);
                window.draw(label_caisse);
            }

            window.display();
        }
    }

    return 0;
}