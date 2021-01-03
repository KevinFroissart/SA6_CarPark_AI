#include "../headers/dataWindow.hpp"

/**
 * @brief Construct a new data Window::data Window object
 * 
 * @param idParking 
 * @param main_b 
 */
dataWindow::dataWindow(int idParking, Main_back *main_b) : id_parking(idParking), main_b(main_b)
{
    currentConv = "";
}

/**
 * @brief Create a new window
 * @return int 
 */
int dataWindow::newWindow()
{
    sf::RenderWindow window;
    int width = 630;
    if (main_b->conversation[id_parking].size() > 17)
        width = main_b->conversation[id_parking - 1].size() * 35 + 35;

    window.create(sf::VideoMode(1400, width), "Parking " + to_string(id_parking) + " - Conversations");

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
            if (main_b->conversation[id_parking - 1].size() > 17)
                width = main_b->conversation[id_parking - 1].size() * 35 + 35;

            window.setSize(sf::Vector2u(1400, width));
            sf::Font font;
            if (!font.loadFromFile("arial.ttf"))
                return EXIT_FAILURE;

            window.clear(sf::Color(210, 210, 210, 255));
            int length = 180;
            int width = 35;
            int i = 0;
            for (map<int, string>::iterator itr_conv = main_b->conversation[id_parking - 1].begin(); itr_conv != main_b->conversation[id_parking - 1].end(); ++itr_conv, i++)
            {
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
            /*sf::Text close_label("Retour", font, 25);
            close_label.setFillColor(sf::Color::Black);
            close_label.move(0.f, ((main_b->conversation[id_parking - 1].size()) * 35) + 3);
            sf::RectangleShape close_button;
            close_button.setOutlineColor(sf::Color::Black);
            close_button.setOutlineThickness(1);
            close_button.setSize(sf::Vector2f(length * 0.80, width));
            close_button.setFillColor(sf::Color::Transparent);
            close_button.move(0.f, ((main_b->conversation[id_parking - 1].size()) * 35));

            if (sf::Mouse::getPosition(window).x > close_button.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (close_button.getGlobalBounds().left + close_button.getGlobalBounds().width) && sf::Mouse::getPosition(window).y > close_button.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (close_button.getGlobalBounds().top + close_button.getGlobalBounds().height))
            {
                close_button.setOutlineColor(sf::Color::White);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    window.close();
                    closed = true;
                }
            }
            window.draw(close_label);
            window.draw(close_button);*/
            // -------- bug
            window.display();
        }
    }
    return 0;
}