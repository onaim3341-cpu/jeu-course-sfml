#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::Font police;
    sf::Text titre;
    sf::Text jouer;
    sf::Text apropos;
    sf::Text quitter;
    sf::Text aide;
    int choix;

public:
    Menu();

    void monter();
    void descendre();
    int getChoix() const;
    void afficher(sf::RenderWindow& fenetre);
};