#pragma once
#include <SFML/Graphics.hpp>

class Entite
{
protected:
    sf::RectangleShape forme;
    sf::Vector2f vitesse;

public:
    Entite();
    virtual ~Entite() = default;

    virtual void mettreAJour(float dt) = 0;
    virtual void dessiner(sf::RenderWindow& fenetre);

    sf::FloatRect getBornes() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
};