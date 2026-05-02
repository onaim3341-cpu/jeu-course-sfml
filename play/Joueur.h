#pragma once
#include "Entite.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <optional>

enum class AnimationJoueur
{
    FrontIdle,
    RightIdle,
    RightRunning,
    RightHurt,
    RightBlinking
};

class Joueur : public Entite
{
private:
    float gravite;
    float forceSaut;
    float positionSol;
    float positionHaut;
    bool surSol;
    bool accroupi;
    bool tombeDansTrou;

    float hauteurNormale;
    float hauteurAccroupie;
    int typePersonnage;
    float tempsAnimation;

    std::optional<sf::Sprite> sprite;
    std::map<AnimationJoueur, std::vector<sf::Texture>> animations;
    AnimationJoueur animationActuelle;
    
    float tempsFrame;
    float dureeFrame;
    bool animationHurtActive;
    float tempsHurt;
    float animationTimer;
    float animationVitesse;
    int frameActuelle;

private:
    std::string getNomPersonnage() const;
    bool chargerSequence(AnimationJoueur anim, const std::string& dossier, const std::string& prefixe, int maxFrames = 20);
    void changerAnimation(AnimationJoueur nouvelleAnimation);
    void mettreAJourSpriteDepuisForme();

public:
    Joueur(float x, float y);

    bool sauter();
    void accroupir();
    void relever();
    void activerHurt();

    void commencerTomber();
    bool estEnTrainDeTomber() const;
    void setPositionSol(float y);

    void reinitialiser(float x, float y);
    void mettreAJour(float dt) override;

    void setTypePersonnage(int type);
    void dessiner(sf::RenderWindow& fenetre) override;
    void arreter();
};

