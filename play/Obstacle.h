#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

enum class TypeObstacle
{
    // bas seulement
    Fire,
    TreeWolf,
    CrystalWhite,
    TreeHuman,
    TotemUp,
    MegaTree,
    CrystalYellow,

    // haut seulement
    BranchesSnow,
    RockSpikes,
    GrassPlatform,
    WoodBranch,
    StonePlatform,
    Coconut
};

enum class PositionObstacle
{
    Bas,
    Haut
};

class Obstacle
{
private:
    TypeObstacle type;
    PositionObstacle positionObstacle;

    sf::RectangleShape forme;
    sf::Vector2f vitesse;

    float vitesseDefilement;
    float solY;
    float plafondY;

    sf::Texture texture;
    std::vector<sf::Texture> frames;

    int frameActuelle;
    float tempsAnimation;
    float dureeFrame;

    void configurerCollision(float x);
    void chargerImages();

public:
    Obstacle(TypeObstacle typeObstacle,
        PositionObstacle position,
        float x,
        float sol,
        float plafond,
        float vitesseObstacle);

    std::string obtenirCheminImage() const;

    void mettreAJour(float dt);
    void dessiner(sf::RenderWindow& fenetre);

    bool estHorsEcran() const;

    TypeObstacle getType() const;
    PositionObstacle getPositionObstacle() const;

    sf::FloatRect getBornes() const
    {
        return forme.getGlobalBounds();
    }
};