#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define SIZE 200

void reset(int(&grid)[3][3], int& counter, bool& turn_lock, sf::Text& text, bool& end)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            grid[i][j] = 0;
        }
    }

    end = false;
    text.setString("");
    counter = 0;
    turn_lock = true;
}

bool winCheck(int(&grid)[3][3], int symb)
{
    for (int i = 0; i < 3; i++)
    {
        bool rows = true, cols = true;

        for (int j = 0; j < 3; j++)
        {
            rows &= grid[i][j] == symb;
            cols &= grid[j][i] == symb;
        }

        if (rows || cols) return true;
    }

    bool leftD = true, rightD = true;

    for (int i = 0; i < 3; i++)
    {
        leftD &= grid[i][i] == symb;
        rightD &= grid[2 - i][i] == symb;
    }

    if (leftD || rightD) return true;

    return false;
}

int main()
{
    int counter = 0;

    bool end = false;
    bool turn_lock = true;

    sf::Vector2i mousePos;

    int grid[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

    sf::RenderWindow window(sf::VideoMode(600, 600), "tic-tac-toe");

    sf::Image icon;
    icon.loadFromFile("source/favicon.png");
    window.setIcon(64, 64, icon.getPixelsPtr());

    sf::Texture texture;
    texture.loadFromFile("source/texture.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Font font;
    font.loadFromFile("source/font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(128);
    text.setPosition(sf::Vector2f(175, 200));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(10);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        mousePos = sf::Mouse::getPosition(window);
        int mousePosX = mousePos.x / SIZE;
        int mousePosY = mousePos.y / SIZE;

        if (event.mouseButton.button == sf::Mouse::Left && grid[mousePosX][mousePosY] == 0 && turn_lock && !end)
        {
            grid[mousePosX][mousePosY] = 1;
            turn_lock = !turn_lock;
            counter++;
        }
        if (event.mouseButton.button == sf::Mouse::Right && grid[mousePosX][mousePosY] == 0 && !turn_lock && !end)
        {
            grid[mousePosX][mousePosY] = 2;
            turn_lock = !turn_lock;
            counter++;
        }

        if (winCheck(grid, 1))
        {
            end = true;
            text.setString("O win!");
            if (event.key.code == sf::Keyboard::Space)
            {
                reset(grid, counter, turn_lock, text, end);
            }
        }
        if (winCheck(grid, 2))
        {
            end = true;
            text.setString("X win!");
            if (event.key.code == sf::Keyboard::Space)
            {
                reset(grid, counter, turn_lock, text, end);
            }
        }
        if (counter == 9)
        {
            end = true;
            text.setString("Draw!");
            if (event.key.code == sf::Keyboard::Space)
            {
                reset(grid, counter, turn_lock, text, end);
            }
        }

        window.clear();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                sprite.setTextureRect(sf::IntRect(SIZE * grid[i][j], 0, SIZE * grid[i][j] + SIZE, SIZE));
                sprite.setPosition(sf::Vector2f(SIZE * i, SIZE * j));
                window.draw(sprite);
            }
        }

        window.draw(text);

        window.display();
    }
}
//hi there!