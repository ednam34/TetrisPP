#pragma once

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <string>
#include <cmath>
#include "Grid.hpp"
#include "Shape.hpp"


class Game
{
private:
    Grid grd;
    sf::Font font;
    sf::Text text;
    sf::Text scoreTxt;
    sf::Text nextPiece;
    sf::Text looseText;
    sf::Texture blockTexture;
    //Shape actual;
    //Shape next;
public:
    Game();
    void window();
    void game(sf::Clock &clock, sf::Time &descentDelay,bool &fast,sf::RenderWindow &window);
    void loose(sf::Clock &clock, sf::Time &descentDelay,bool &fast,sf::RenderWindow &window);
    void setCaseColor(sf::RectangleShape& cell,sf::RenderWindow& window);
    void drawNextPiece(sf::RectangleShape& cell,sf::RenderWindow& window);
    void drawScore(sf::RenderWindow& window);
    void drawLoose(sf::RenderWindow& window);

};




