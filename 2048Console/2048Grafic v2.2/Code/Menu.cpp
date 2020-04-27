#include "game.h"

void menu(sf::RenderWindow &window)
{
    int position = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                if (Exit())
                {
                    window.close();
                }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
            {
                if (position == 4)
                    position = 1;
                else position++;
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
            {
                if (position == 1)
                    position = 4;
                else position--;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                switch (position)
                {
                case 1:
                    game(4, window);
                    break;
                case 2:
                    prev_game(4, window);
                    break;
                case 3:
                    show_scores(window);
                    break;
                case 4:
                    if(Exit())
                        window.close();
                    break;
                }
        }

        window.clear();
        
        sf::RectangleShape option;
        option.setFillColor(sf::Color::White);
        option.setSize(sf::Vector2f(600, 100));
        option.setPosition(200, 100);
        sf::Text text1;
        sf::Font font;
        font.loadFromFile("bold.ttf");
        text1.setCharacterSize(50);
        text1.setFont(font);
        text1.setFillColor(sf::Color::Blue);
        text1.setStyle(sf::Text::Bold);
        text1.setString("New Game");
        text1.setPosition(400, 110);
        sf::Text text2 = text1, text3 = text1, text4 = text1;
        switch (position)
        {
        case 1:
            text1.setFillColor(sf::Color::Yellow);
            text1.setStyle(sf::Text::Underlined);
            break;
        case 2:
            text2.setFillColor(sf::Color::Yellow);
            text2.setStyle(sf::Text::Underlined);
            break;
        case 3:
            text3.setFillColor(sf::Color::Yellow);
            text3.setStyle(sf::Text::Underlined);
            break;
        case 4:
            text4.setFillColor(sf::Color::Yellow);
            text4.setStyle(sf::Text::Underlined);
            break;
        }

        window.draw(option);
        window.draw(text1);
        
        option.setPosition(200, 250);
        text2.setString("Continue");
        text2.setPosition(410, 260);
        window.draw(option);
        window.draw(text2);

        option.setPosition(200, 400);
        text3.setString("Records");
        text3.setPosition(420, 410);
        window.draw(option);
        window.draw(text3);

        option.setPosition(200, 550);
        text4.setString("Exit");
        text4.setPosition(460, 560);
        window.draw(option);
        window.draw(text4);
        
        window.display();
    }
}