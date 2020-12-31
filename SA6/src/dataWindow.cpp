#include "dataWindow.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
using namespace std;

int dataWindow::newWindow()
{

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 450), "Parking x infos");

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
                closed = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::A)
                {
                    window.close();
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

            window.clear(sf::Color(210, 210, 210, 255));
            window.display();
        }
    }
}