#include "Joueur.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Joueur::Joueur(float x, float ySol)
{
    gravite = 1000.f;
    forceSaut = -850.f;

    // Grande hitbox pour garder la collision correcte
    hauteurNormale = 120.f;
    hauteurAccroupie = 60.f;

    positionSol = ySol;
    positionHaut = 0.f;

    surSol = true;
    accroupi = false;
    tombeDansTrou = false;

    typePersonnage = 0;
    tempsAnimation = 0.f;

    animationActuelle = AnimationJoueur::RightIdle;
    frameActuelle = 0;
    tempsFrame = 0.f;
    dureeFrame = 0.08f;

    animationHurtActive = false;
    tempsHurt = 0.f;

    animationTimer = 0.f;
    animationVitesse = 0.08f;

    vitesse = { 0.f, 0.f };

    // Hitbox collision
    forme.setSize({ 55.f, hauteurNormale });
    forme.setFillColor(sf::Color(255, 255, 255, 0));
    forme.setPosition({ x, positionSol - hauteurNormale });
}

std::string Joueur::getNomPersonnage() const
{
    switch (typePersonnage)
    {
    case 0:  return "Chief";
    case 1:  return "Female";
    case 2:  return "Male";
    default: return "Chief";
    }
}

bool Joueur::chargerSequence(AnimationJoueur anim, const std::string& dossier, const std::string& prefixe, int maxFrames)
{
    std::vector<sf::Texture> frames;

    for (int i = 0; i < maxFrames; i++)
    {
        std::ostringstream chemin;
        chemin << dossier << "/" << prefixe
            << std::setfill('0') << std::setw(3) << i << ".png";

        sf::Texture texture;
        if (!texture.loadFromFile(chemin.str()))
            break;

        frames.push_back(std::move(texture));
    }

    if (frames.empty())
    {
        std::cout << "Erreur chargement animation : " << dossier << std::endl;
        return false;
    }

    animations[anim] = std::move(frames);
    return true;
}

void Joueur::changerAnimation(AnimationJoueur nouvelleAnimation)
{
    if (animationActuelle == nouvelleAnimation &&
        animations.count(nouvelleAnimation) > 0 &&
        !animations[nouvelleAnimation].empty())
        return;

    animationActuelle = nouvelleAnimation;
    frameActuelle = 0;
    tempsFrame = 0.f;

    if (animations.count(animationActuelle) > 0 && !animations[animationActuelle].empty())
    {
        if (!sprite.has_value())
            sprite.emplace(animations[animationActuelle][0]);
        else
            sprite->setTexture(animations[animationActuelle][0], true);
    }
}

void Joueur::mettreAJourSpriteDepuisForme()
{
    if (!sprite.has_value())
        return;

    sf::Vector2f pos = forme.getPosition();
    sf::Vector2f tailleHitbox = forme.getSize();

    // Joueur plus petit VISUELLEMENT seulement
    if (accroupi)
        sprite->setScale({ 0.48f, 0.22f });
    else
        sprite->setScale({ 0.48f, 0.34f });

    sf::FloatRect bounds = sprite->getGlobalBounds();

    float xSprite = pos.x + (tailleHitbox.x - bounds.size.x) / 2.f + 12.f;
    float ySprite = pos.y + tailleHitbox.y - bounds.size.y;

    sprite->setPosition({ xSprite, ySprite });
}

void Joueur::arreter()
{
    vitesse.x = 0.f;
}

bool Joueur::sauter()
{
    if (surSol && !tombeDansTrou)
    {
        relever();
        vitesse.y = forceSaut;
        surSol = false;
        return true;
    }
    return false;
}

void Joueur::accroupir()
{
    if (surSol && !accroupi && !tombeDansTrou)
    {
        float x = forme.getPosition().x;
        float bas = forme.getPosition().y + forme.getSize().y;

        forme.setSize({ 55.f, hauteurAccroupie });
        forme.setPosition({ x, bas - hauteurAccroupie });

        accroupi = true;
        mettreAJourSpriteDepuisForme();
    }
}

void Joueur::relever()
{
    if (accroupi && !tombeDansTrou)
    {
        float x = forme.getPosition().x;
        float bas = forme.getPosition().y + forme.getSize().y;

        forme.setSize({ 55.f, hauteurNormale });
        forme.setPosition({ x, bas - hauteurNormale });

        accroupi = false;
        mettreAJourSpriteDepuisForme();
    }
}

void Joueur::activerHurt()
{
    animationHurtActive = true;
    tempsHurt = 0.f;
}

void Joueur::setTypePersonnage(int type)
{
    typePersonnage = type;
    animations.clear();

    std::string base = "Joueurs/" + getNomPersonnage();

    bool ok = true;
    ok &= chargerSequence(AnimationJoueur::FrontIdle, base + "/Front - Idle", "Front - Idle_", 10);
    ok &= chargerSequence(AnimationJoueur::RightIdle, base + "/Right - Idle", "Right - Idle_", 10);
    ok &= chargerSequence(AnimationJoueur::RightRunning, base + "/Right - Running", "Right - Running_", 10);
    ok &= chargerSequence(AnimationJoueur::RightHurt, base + "/Right - Hurt", "Right - Hurt_", 10);
    ok &= chargerSequence(AnimationJoueur::RightBlinking, base + "/Right - Idle Blinking", "Right - Idle Blinking_", 10);

    if (!ok)
        std::cout << "Impossible de charger toutes les animations : " << getNomPersonnage() << std::endl;

    changerAnimation(AnimationJoueur::RightIdle);
    mettreAJourSpriteDepuisForme();
}

void Joueur::commencerTomber()
{
    if (!tombeDansTrou)
    {
        tombeDansTrou = true;
        surSol = false;
        vitesse.y = 250.f;
    }
}

bool Joueur::estEnTrainDeTomber() const
{
    return tombeDansTrou;
}

void Joueur::setPositionSol(float y)
{
    positionSol = y;
}

void Joueur::reinitialiser(float x, float ySol)
{
    positionSol = ySol;

    forme.setSize({ 55.f, hauteurNormale });
    forme.setPosition({ x, positionSol - hauteurNormale });

    vitesse = { 0.f, 0.f };
    surSol = true;
    accroupi = false;
    tombeDansTrou = false;
    tempsAnimation = 0.f;
    animationHurtActive = false;
    tempsHurt = 0.f;
    tempsFrame = 0.f;
    frameActuelle = 0;

    changerAnimation(AnimationJoueur::RightIdle);
    mettreAJourSpriteDepuisForme();
}

void Joueur::mettreAJour(float dt)
{
    tempsAnimation += dt * 10.f;
    tempsFrame += dt;

    vitesse.y += gravite * dt;
    forme.move({ 0.f, vitesse.y * dt });

    if (tombeDansTrou)
    {
        mettreAJourSpriteDepuisForme();
        return;
    }

    if (forme.getPosition().y < positionHaut)
    {
        forme.setPosition({ forme.getPosition().x, positionHaut });
        vitesse.y = 0.f;
    }

    float hauteurActuelle = accroupi ? hauteurAccroupie : hauteurNormale;
    float ySolHitbox = positionSol - hauteurActuelle;

    if (forme.getPosition().y >= ySolHitbox)
    {
        forme.setPosition({ forme.getPosition().x, ySolHitbox });
        vitesse.y = 0.f;
        surSol = true;
    }
    else
    {
        surSol = false;
    }

    if (animationHurtActive)
    {
        changerAnimation(AnimationJoueur::RightHurt);
        tempsHurt += dt;
        if (tempsHurt >= 0.5f)
        {
            animationHurtActive = false;
            tempsHurt = 0.f;
        }
    }
    else
    {
        changerAnimation(AnimationJoueur::RightRunning);
    }

    auto& frames = animations[animationActuelle];
    if (!frames.empty() && tempsFrame >= dureeFrame)
    {
        tempsFrame = 0.f;
        frameActuelle = (frameActuelle + 1) % static_cast<int>(frames.size());

        if (!sprite.has_value())
            sprite.emplace(frames[frameActuelle]);
        else
            sprite->setTexture(frames[frameActuelle], true);
    }

    mettreAJourSpriteDepuisForme();
}

void Joueur::dessiner(sf::RenderWindow& fenetre)
{
    if (sprite.has_value())
        fenetre.draw(*sprite);
}