#include "Entite.h"

Entite::Entite() : vitesse(0.f, 0.f)
{
}

void Entite::dessiner(sf::RenderWindow& fenetre)
{
    fenetre.draw(forme);
}

sf::FloatRect Entite::getBornes() const
{
    return forme.getGlobalBounds();
}

void Entite::setPosition(float x, float y)
{
    forme.setPosition({ x, y });
}

sf::Vector2f Entite::getPosition() const
{
    return forme.getPosition();
}