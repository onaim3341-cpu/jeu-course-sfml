#include "Menu.h"
#include <iostream>

Menu::Menu()
    : titre(police, "", 48),
    jouer(police, "", 34),
    apropos(police, "", 34),
    quitter(police, "", 34),
    aide(police, "", 22),
    choix(0)
{
    if (!police.openFromFile("assets/arial.ttf"))
        std::cout << "Erreur chargement police menu" << std::endl;
    else
        std::cout << "Police menu chargee avec succes" << std::endl;

    titre.setString("Jeu de cachette");
    jouer.setString("Jouer");
    apropos.setString("A propos");
    quitter.setString("Quitter");
    aide.setString("Haut / Bas pour choisir - Entree pour valider");

    titre.setStyle(sf::Text::Bold | sf::Text::Italic);

    titre.setPosition({ 300.f, 80.f });
    jouer.setPosition({ 445.f, 205.f });
    apropos.setPosition({ 425.f, 285.f });
    quitter.setPosition({ 440.f, 365.f });
    aide.setPosition({ 220.f, 485.f });
    aide.setOutlineThickness(1.f);

    titre.setOutlineThickness(2.f);
    jouer.setOutlineThickness(1.f);
    apropos.setOutlineThickness(1.f);
    quitter.setOutlineThickness(1.f);
    aide.setOutlineThickness(1.f);

    titre.setOutlineColor(sf::Color(25, 45, 20));
    jouer.setOutlineColor(sf::Color(20, 35, 18));
    apropos.setOutlineColor(sf::Color(20, 35, 18));
    quitter.setOutlineColor(sf::Color(20, 35, 18));
    aide.setOutlineColor(sf::Color(20, 35, 18));
}

void Menu::monter()
{
    if (choix > 0)
        choix--;
}

void Menu::descendre()
{
    if (choix < 2)
        choix++;
}

int Menu::getChoix() const
{
    return choix;
}

void Menu::afficher(sf::RenderWindow& fenetre)
{
    sf::RectangleShape panneau({ 500.f, 300.f });
    panneau.setPosition({ 250.f, 140.f });
    panneau.setFillColor(sf::Color(18, 45, 24, 160));
    panneau.setOutlineThickness(3.f);
    panneau.setOutlineColor(sf::Color(186, 158, 92, 210));

    sf::RectangleShape decoHaut({ 240.f, 8.f });
    decoHaut.setPosition({ 380.f, 60.f });
    decoHaut.setFillColor(sf::Color(186, 158, 92));

    sf::RectangleShape decoBas({ 340.f, 6.f });
    decoBas.setPosition({ 330.f, 465.f });
    decoBas.setFillColor(sf::Color(140, 110, 60));

    sf::RectangleShape boutonJouer({ 260.f, 52.f });
    boutonJouer.setPosition({ 370.f, 195.f });
    boutonJouer.setOutlineThickness(2.f);

    sf::RectangleShape boutonApropos({ 260.f, 52.f });
    boutonApropos.setPosition({ 370.f, 275.f });
    boutonApropos.setOutlineThickness(2.f);

    sf::RectangleShape boutonQuitter({ 260.f, 52.f });
    boutonQuitter.setPosition({ 370.f, 355.f });
    boutonQuitter.setOutlineThickness(2.f);

    auto appliquerStyleBouton = [](sf::RectangleShape& bouton, bool selectionne)
        {
            if (selectionne)
            {
                bouton.setFillColor(sf::Color(196, 170, 95, 220));
                bouton.setOutlineColor(sf::Color(245, 235, 200, 240));
            }
            else
            {
                bouton.setFillColor(sf::Color(35, 70, 40, 170));
                bouton.setOutlineColor(sf::Color(180, 200, 160, 150));
            }
        };

    appliquerStyleBouton(boutonJouer, choix == 0);
    appliquerStyleBouton(boutonApropos, choix == 1);
    appliquerStyleBouton(boutonQuitter, choix == 2);

    titre.setFillColor(sf::Color(240, 232, 200));

    jouer.setFillColor(choix == 0 ? sf::Color(84, 107, 65) : sf::Color(245, 244, 228));
    apropos.setFillColor(choix == 1 ? sf::Color(84, 107, 65) : sf::Color(245, 244, 228));
    quitter.setFillColor(choix == 2 ? sf::Color(84, 107, 65) : sf::Color(245, 244, 228));

    jouer.setStyle(choix == 0 ? sf::Text::Bold : sf::Text::Regular);
    apropos.setStyle(choix == 1 ? sf::Text::Bold : sf::Text::Regular);
    quitter.setStyle(choix == 2 ? sf::Text::Bold : sf::Text::Regular);

    aide.setFillColor(sf::Color(225, 235, 210));
    aide.setStyle(sf::Text::Bold | sf::Text::Italic);

    sf::CircleShape point1(5.f);
    point1.setFillColor(sf::Color(210, 185, 90));
    point1.setPosition({ 280.f, 95.f });

    sf::CircleShape point2(5.f);
    point2.setFillColor(sf::Color(210, 185, 90));
    point2.setPosition({ 710.f, 95.f });

    fenetre.draw(panneau);
    fenetre.draw(decoHaut);
    fenetre.draw(decoBas);

    fenetre.draw(boutonJouer);
    fenetre.draw(boutonApropos);
    fenetre.draw(boutonQuitter);

    fenetre.draw(point1);
    fenetre.draw(point2);

    fenetre.draw(titre);
    fenetre.draw(jouer);
    fenetre.draw(apropos);
    fenetre.draw(quitter);
    fenetre.draw(aide);
}