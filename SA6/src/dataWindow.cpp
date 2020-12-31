#include "../headers/dataWindow.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <unistd.h>

dataWindow::dataWindow(int idParking) : id_parking(idParking)
{
}

int dataWindow::newWindow()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 450), "Parking " + to_string(id_parking) + " - Conversations");

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
            sf::Text text("Parking ", font, 40);
            text.setFillColor(sf::Color::Black);

            window.clear(sf::Color(210, 210, 210, 255));
            window.draw(text);
            window.display();
        }
    }
    return 0;
}