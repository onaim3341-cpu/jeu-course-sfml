#include "Obstacle.h"
#include <iostream>
#include <iomanip>
#include <sstream>

std::string Obstacle::obtenirCheminImage() const
{
    switch (type)
    {
        // bas seulement
    case TypeObstacle::Fire:
        return "assets/obstacles/flame_png/00.png";
    case TypeObstacle::TreeWolf:
        return "assets/obstacles/roche.png";
    case TypeObstacle::CrystalWhite:
        return "assets/obstacles/White_crystal1.png";
    case TypeObstacle::TreeHuman:
        return "assets/obstacles/Tree_idol_human.png";
    case TypeObstacle::TotemUp:
        return "assets/obstacles/Jump_Bonus_02.png";
    case TypeObstacle::MegaTree:
        return "assets/obstacles/Beige_green_mushroom1.png";
    case TypeObstacle::CrystalYellow:
        return "assets/obstacles/Yellow-green_crystal1.png";

        // haut seulement
    case TypeObstacle::BranchesSnow:
        return "assets/obstacles/prop5.png";
    case TypeObstacle::RockSpikes:
        return "assets/obstacles/Pad_01_2.png";
    case TypeObstacle::GrassPlatform:
        return "assets/obstacles/Pad_02_1.png";
    case TypeObstacle::WoodBranch:
        return "assets/obstacles/Prop_4.png";
    case TypeObstacle::StonePlatform:
        return "assets/obstacles/Flight_Bonus_01.png";
    case TypeObstacle::Coconut:
        return "assets/obstacles/verteOb.png";
    }

    return "";
}

Obstacle::Obstacle(TypeObstacle typeObstacle,
    PositionObstacle position,
    float x,
    float sol,
    float plafond,
    float vitesseObstacle)
{
    type = typeObstacle;
    positionObstacle = position;
    vitesseDefilement = vitesseObstacle;
    solY = sol;
    plafondY = plafond;
    vitesse = { 0.f, 0.f };

    frameActuelle = 0;
    tempsAnimation = 0.f;
    dureeFrame = 0.05f;

    configurerCollision(x);
    chargerImages();

    forme.setFillColor(sf::Color(255, 0, 0, 120));
}

void Obstacle::chargerImages()
{
    if (type == TypeObstacle::Fire)
    {
        for (int i = 0; i <= 27; i++)
        {
            std::ostringstream chemin;
            chemin << "assets/obstacles/flame_png/"
                << std::setw(2) << std::setfill('0') << i
                << ".png";

            sf::Texture tex;
            if (tex.loadFromFile(chemin.str()))
            {
                frames.push_back(std::move(tex));
            }
            else
            {
                std::cout << "Erreur chargement image : " << chemin.str() << std::endl;
            }
        }

        if (frames.empty())
        {
            std::cout << "Aucune image du feu n'a ete chargee." << std::endl;
        }
    }
    else
    {
        std::string chemin = obtenirCheminImage();
        if (!texture.loadFromFile(chemin))
        {
            std::cout << "Erreur chargement image : " << chemin << std::endl;
        }
    }
}

void Obstacle::configurerCollision(float x)
{
    if (positionObstacle == PositionObstacle::Bas)
    {
        switch (type)
        {
        case TypeObstacle::Fire:
            forme.setSize({ 95.f, 135.f });
            forme.setPosition({ x, solY - 165.f });
            break;

        case TypeObstacle::TreeWolf:
            forme.setSize({ 155.f, 150.f });
            forme.setPosition({ x, solY - 150.f });
            break;

        case TypeObstacle::CrystalWhite:
            forme.setSize({ 75.f, 86.f });
            forme.setPosition({ x, solY - 105.f });
            break;

        case TypeObstacle::TreeHuman:
            forme.setSize({ 110.f, 130.f });
            forme.setPosition({ x, solY - 150.f });
            break;

        case TypeObstacle::TotemUp:
            forme.setSize({ 95.f, 145.f });
            forme.setPosition({ x, solY - 180.f });
            break;

        case TypeObstacle::MegaTree:
            forme.setSize({ 145.f, 185.f });
            forme.setPosition({ x, solY - 170.f });
            break;

        case TypeObstacle::CrystalYellow:
            forme.setSize({ 75.f, 85.f });
            forme.setPosition({ x, solY - 105.f });
            break;

        default:
            forme.setSize({ 90.f, 90.f });
            forme.setPosition({ x, solY - 140.f });
            break;
        }
    }
   
    else
{
    switch (type)
    {
    case TypeObstacle::BranchesSnow:
        forme.setSize({ 150.f, 120.f }); 
        forme.setPosition({ x, solY - 225.f });
        break;

    case TypeObstacle::RockSpikes:
        forme.setSize({ 140.f, 120.f });
        forme.setPosition({ x, solY - 225.f });
        break;

    case TypeObstacle::GrassPlatform:
        forme.setSize({ 150.f, 105.f });
        forme.setPosition({ x, solY - 215.f });
        break;

    case TypeObstacle::WoodBranch:
        forme.setSize({ 125.f, 90.f });
        forme.setPosition({ x, solY - 205.f });
        break;

    case TypeObstacle::StonePlatform:
        forme.setSize({ 130.f, 115.f });
        forme.setPosition({ x, solY - 220.f });
        break;

    case TypeObstacle::Coconut:
        forme.setSize({ 190.f, 120.f });
        forme.setPosition({ x, solY - 200.f });
        break;

    default:
        forme.setSize({ 100.f, 110.f });
        forme.setPosition({ x, solY - 215.f });
        break;
    }
}
}

void Obstacle::mettreAJour(float dt)
{
    forme.move({ -vitesseDefilement * dt, 0.f });

    if (type == TypeObstacle::Fire && !frames.empty())
    {
        tempsAnimation += dt;
        if (tempsAnimation >= dureeFrame)
        {
            tempsAnimation = 0.f;
            frameActuelle = (frameActuelle + 1) % static_cast<int>(frames.size());
        }
    }
}

bool Obstacle::estHorsEcran() const
{
    return forme.getPosition().x + forme.getSize().x < 0.f;
}

TypeObstacle Obstacle::getType() const
{
    return type;
}

PositionObstacle Obstacle::getPositionObstacle() const
{
    return positionObstacle;
}

void Obstacle::dessiner(sf::RenderWindow& fenetre)
{
    if (type == TypeObstacle::Fire)
    {
        if (frames.empty())
            return;

        sf::Sprite sprite(frames[frameActuelle]);
        sprite.setPosition(forme.getPosition());

        sprite.setScale({
            forme.getSize().x / static_cast<float>(frames[frameActuelle].getSize().x),
            forme.getSize().y / static_cast<float>(frames[frameActuelle].getSize().y)
            });

        fenetre.draw(sprite);

    }
    else
    {
        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return;

        sf::Sprite sprite(texture);
        sprite.setPosition(forme.getPosition());

        sprite.setScale({
            forme.getSize().x / static_cast<float>(texture.getSize().x),
            forme.getSize().y / static_cast<float>(texture.getSize().y)
            });

        fenetre.draw(sprite);
    }
}