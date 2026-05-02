#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <optional>
#include "Menu.h"
#include "Joueur.h"
#include "Obstacle.h"

enum class Etat
{
    Menu,
    ChoixPersonnage,
    EnJeu,
    Pause,
    Fin,
    Victoire,
    APropos
};

class Jeu
{
private:
    sf::RenderWindow fenetre;
    sf::Font police;
    sf::Font policeGameOver;
    sf::Font Marona3DExtrude_MAlJY;

    sf::Texture textureFond;
    sf::Sprite fond1;
    sf::Sprite fond2;
    bool backgroundCharge;

    sf::Texture textureChoixChief;
    sf::Texture textureChoixFemale;
    sf::Texture textureChoixMale;

    std::optional<sf::Sprite> spriteChoixChief;
    std::optional<sf::Sprite> spriteChoixFemale;
    std::optional<sf::Sprite> spriteChoixMale;

    sf::Text texteScore;
    sf::Text texteFin;
    sf::Text texteInfo;
    sf::Text texteChrono;
    sf::Texture textureRedHeart;
    sf::Texture textureGrayHeart;

    std::optional<sf::Sprite> coeur1;
    std::optional<sf::Sprite> coeur2;
    std::optional<sf::Sprite> coeur3;

    sf::Text texteAPropos;
    sf::Text titreAPropos;
    sf::Text texteVictoire;
    sf::Text texteBravo;
    sf::Text introAPropos;
    sf::Text fabricationTitre;
    sf::Text fabricationListe;
    sf::Text touchesTitre;
    sf::Text touchesListe;
    sf::Text finAPropos;
   

    sf::Text textePauseTitre;
    sf::Text textePauseInfo;

    int choixPersonnage;
    sf::Text titreChoix;
    sf::Text option1;
    sf::Text option2;
    sf::Text option3;
    sf::Text option4;
    sf::Text infoChoix;
    int personnageSelectionne;

    Menu menu;
    Joueur joueur;
    std::vector<Obstacle> obstacles;

    Etat etat;

    float tempsObstacle;
    float delaiObstacle;
    int score;
    float tempsRestant;
    float tempsMax;

    float decalageFond1;
    float decalageFond2;

    bool collisionEnCours;
    float tempsCollision;

    int nbTouches;
    int maxTouches;
    bool invulnerable;
    float tempsInvulnerable;

    sf::RectangleShape sol;
    sf::RectangleShape barreTempsFond;
    sf::RectangleShape barreTemps;

    sf::RectangleShape barreTempsCentreFond;
    sf::CircleShape barreTempsGaucheFond;
    sf::CircleShape barreTempsDroiteFond;

    sf::RectangleShape barreTempsCentre;
    sf::CircleShape barreTempsGauche;
    sf::CircleShape barreTempsDroite;

    sf::SoundBuffer tamponSaut;
    sf::SoundBuffer tamponCollision;
    sf::SoundBuffer tamponVictoire;
    sf::SoundBuffer tamponEchec;

    sf::Sound sonSaut;
    sf::Sound sonCollision;
    sf::Sound sonVictoire;
    sf::Sound sonEchec;

    sf::Music musiqueFond;

    bool audioDisponible;
    bool sonVictoireJoue;
    bool sonEchecJoue;


    float vitesseJeu;
    float vitesseMin;
    float vitesseMax;
    float pasVitesse;


public:
    Jeu();
    
    void executer();
    void gererEvenements();
    void mettreAJour(float dt);
    void mettreAJourJeu(float dt);
    void creerObstacle();
    void reinitialiserJeu();
    bool verifierCollision() const;
    void dessinerArrierePlan();
    void dessinerBackgroundFin();
    void dessinerAPropos();
    void afficher();
    void dessinerChoixPersonnage();
    void dessinerMiniPersonnage(float x, float y, int type, bool selectionne);

};