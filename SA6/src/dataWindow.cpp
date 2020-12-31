#include "../headers/dataWindow.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <unistd.h>
#include <iostream>

dataWindow::dataWindow(int idParking, map<int, map<int, string>> conversation) : id_parking(idParking), conversation(conversation)
{
    currentConv = "";
}

int dataWindow::newWindow()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(1200, 650), "Parking " + to_string(id_parking) + " - Conversations");

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

            int i = 0;
            for (map<int, string>::iterator itr_conv = conversation[id_parking - 1].begin(); itr_conv != conversation[id_parking - 1].end(); ++itr_conv, i++)
            {
                int length = 180;
                int width = 35;
                int y = i * width;

                sf::Text label("Voiture " + to_string(itr_conv->first), font, 25);
                label.setFillColor(sf::Color::Black);
                label.move(0.f, y + 3);

                sf::RectangleShape button;
                button.setOutlineColor(sf::Color::Black);
                button.setOutlineThickness(1);
                button.setSize(sf::Vector2f(length * 0.80, width));
                button.setFillColor(sf::Color::Transparent);
                button.move(0.f, y);

                sf::Text conv(currentConv, font, 25);
                conv.setFillColor(sf::Color::Black);
                conv.move(180.f, 25);

                if (sf::Mouse::getPosition(window).x > button.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (button.getGlobalBounds().left + button.getGlobalBounds().width) && sf::Mouse::getPosition(window).y > button.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (button.getGlobalBounds().top + button.getGlobalBounds().height))
                {
                    button.setOutlineColor(sf::Color::White);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        button.setFillColor(sf::Color::White);
                        currentConv = itr_conv->second;
                    }
                }
                window.draw(conv);
                window.draw(label);
                window.draw(button);
            }

            window.display();
        }
    }
    return 0;
}