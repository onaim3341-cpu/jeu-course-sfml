#include "Jeu.h"
#include <iostream>
#include <optional>
#include <string>
#include <cstdlib>
#include <ctime>

static const float SOL_Y = 480.f;

Jeu::Jeu()
    : fenetre(sf::VideoMode({ 1000, 550 }), "Jeu de cachette"),
    fond1(textureFond),
    fond2(textureFond),
    texteScore(police, "", 26),
    texteFin(police, "", 40),
    texteInfo(police, "", 24),
    texteChrono(police, "", 24),
    texteAPropos(police, "", 24),
    titreAPropos(police, "", 38),
    texteVictoire(police, "", 40),
    texteBravo(police, "", 24),
    introAPropos(police, "", 22),
    fabricationTitre(police, "", 24),
    fabricationListe(police, "", 22),
    touchesTitre(police, "", 24),
    touchesListe(police, "", 22),
    finAPropos(police, "", 22),
    textePauseTitre(police, "", 42),
    textePauseInfo(police, "", 24),
    choixPersonnage(0),
    personnageSelectionne(0),
    titreChoix(police, "", 34),
    option1(police, "", 24),
    option2(police, "", 24),
    option3(police, "", 24),
    option4(police, "", 24),
    infoChoix(police, "", 20),
    menu(),
    joueur(200.f, SOL_Y),
    etat(Etat::Menu),
    tempsObstacle(0.f),
    delaiObstacle(1.8f),
    score(0),
    tempsRestant(30.f),
    tempsMax(30.f),
    decalageFond1(0.f),
    decalageFond2(0.f),
    collisionEnCours(false),
    tempsCollision(0.f),
    nbTouches(0),
    maxTouches(3),
    invulnerable(false),
    tempsInvulnerable(0.f),
    sonSaut(tamponSaut),
    sonCollision(tamponCollision),
    sonVictoire(tamponVictoire),
    sonEchec(tamponEchec),
    audioDisponible(false),
    sonVictoireJoue(false),
    sonEchecJoue(false),
    backgroundCharge(false)

{
    fenetre.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!police.openFromFile("assets/arial.ttf"))
        std::cout << "Erreur chargement police principale" << std::endl;
    else
        std::cout << "Police principale chargee avec succes" << std::endl;

    if (!policeGameOver.openFromFile("assets/Marona3DExtrude_MAlJY.ttf"))
        std::cout << "Erreur chargement police Game Over" << std::endl;
    else
        std::cout << "Police Game Over chargee avec succes" << std::endl;

    if (textureChoixChief.loadFromFile("Joueurs/Chief/Front - Idle/Front - Idle_000.png"))
    {
        spriteChoixChief.emplace(textureChoixChief);
        spriteChoixChief->setScale({ 0.75f, 0.75f });
        sf::FloatRect b = spriteChoixChief->getLocalBounds();
        spriteChoixChief->setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
        spriteChoixChief->setPosition({ 155.f, 255.f });
    }
    else
    {
        std::cout << "Erreur chargement image choix Chief" << std::endl;
    }

    if (textureChoixFemale.loadFromFile("Joueurs/Female/Front - Idle/Front - Idle_000.png"))
    {
        spriteChoixFemale.emplace(textureChoixFemale);
        spriteChoixFemale->setScale({ 0.72f, 0.72f });
        sf::FloatRect b = spriteChoixFemale->getLocalBounds();
        spriteChoixFemale->setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
        spriteChoixFemale->setPosition({ 445.f, 255.f });
    }
    else
    {
        std::cout << "Erreur chargement image choix Female" << std::endl;
    }

    if (textureChoixMale.loadFromFile("Joueurs/Male/Front - Idle/Front - Idle_000.png"))
    {
        spriteChoixMale.emplace(textureChoixMale);
        spriteChoixMale->setScale({ 0.83f, 0.83f });
        sf::FloatRect b = spriteChoixMale->getLocalBounds();
        spriteChoixMale->setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
        spriteChoixMale->setPosition({ 735.f, 255.f });
    }
    else
    {
        std::cout << "Erreur chargement image choix Male" << std::endl;
    }

    if (textureFond.loadFromFile("assets/background3.png"))
    {
        backgroundCharge = true;
        fond1.setTexture(textureFond, true);
        fond2.setTexture(textureFond, true);

        sf::Vector2u tailleImage = textureFond.getSize();
        fond1.setScale({
            1000.f / static_cast<float>(tailleImage.x),
            550.f / static_cast<float>(tailleImage.y)
            });
        fond2.setScale({
            1000.f / static_cast<float>(tailleImage.x),
            550.f / static_cast<float>(tailleImage.y)
            });

        fond1.setPosition({ 0.f, 0.f });
        fond2.setPosition({ 1000.f, 0.f });

        std::cout << "Background charge avec succes" << std::endl;
    }
    else
    {
        std::cout << "Erreur chargement image background" << std::endl;
    }


    texteScore.setString("Score : 0");
    texteScore.setPosition({ 20.f, 20.f });
    texteScore.setStyle(sf::Text::Bold);
    texteScore.setFillColor(sf::Color(255, 220, 70));
    texteScore.setOutlineColor(sf::Color::Black);
    texteScore.setOutlineThickness(4.f);

    texteChrono.setString("Temps : 30");
    texteChrono.setPosition({ 20.f, 55.f });
    texteChrono.setFillColor(sf::Color(255, 220, 70));
    texteChrono.setStyle(sf::Text::Bold);
    texteChrono.setOutlineColor(sf::Color::Black);
    texteChrono.setOutlineThickness(4.f);

    if (!textureRedHeart.loadFromFile("assets/redHeart.png"))
        std::cout << "Erreur chargement redHeart.png" << std::endl;

    if (!textureGrayHeart.loadFromFile("assets/grayHeart.png"))
        std::cout << "Erreur chargement grayHeart.png" << std::endl;

    coeur1.emplace(textureRedHeart);
    coeur2.emplace(textureRedHeart);
    coeur3.emplace(textureRedHeart);

    coeur1->setPosition({ 810.f, 55.f });
    coeur2->setPosition({ 865.f, 55.f });
    coeur3->setPosition({ 920.f, 55.f });

    coeur1->setScale({ 0.06f, 0.06f });
    coeur2->setScale({ 0.06f, 0.06f });
    coeur3->setScale({ 0.06f, 0.06f });
   
    texteFin.setFont(policeGameOver);
    texteFin.setString("GAME OVER");
    texteFin.setCharacterSize(60);
    texteFin.setStyle(sf::Text::Bold);
    texteFin.setFillColor(sf::Color::White);
    texteFin.setOutlineColor(sf::Color::Black);
    texteFin.setOutlineThickness(4.f);

    sf::FloatRect bFin = texteFin.getLocalBounds();
    texteFin.setOrigin({ bFin.position.x + bFin.size.x / 2.f, 0.f });
    texteFin.setPosition({ 500.f, 120.f });

    
    texteInfo.setFont(police);
    texteInfo.setString(
        "Oups ! \n"
        "Tu t'es pris un obstacle...\n"
        "Essaie encore, tu peux faire mieux !"
    );
    texteInfo.setCharacterSize(26);
    texteInfo.setStyle(sf::Text::Bold);
    texteInfo.setFillColor(sf::Color(245, 245, 245));
    texteInfo.setOutlineColor(sf::Color::Black);
    texteInfo.setOutlineThickness(2.f);

    sf::FloatRect bInfo = texteInfo.getLocalBounds();
    texteInfo.setOrigin({
        bInfo.position.x + bInfo.size.x / 2.f,
        0.f
        });
    texteInfo.setPosition({ 500.f, 230.f });

    titreAPropos.setString("A PROPOS");
    titreAPropos.setCharacterSize(42);
    titreAPropos.setStyle(sf::Text::Bold | sf::Text::Italic);
    titreAPropos.setPosition({ 90.f, 45.f });
    titreAPropos.setFillColor(sf::Color(245, 245, 245));

    introAPropos.setString(
        "Dans ce jeu de course, votre objectif est d'eviter les obstacles\n"
        "et de survivre jusqu'a la fin du chrono."
    );
    introAPropos.setCharacterSize(22);
    introAPropos.setStyle(sf::Text::Bold | sf::Text::Italic);
    introAPropos.setPosition({ 95.f, 125.f });
    introAPropos.setFillColor(sf::Color(245, 245, 245));

    texteVictoire.setFont(policeGameOver);
    texteVictoire.setString("VICTOIRE !");
    texteVictoire.setCharacterSize(52);
    texteVictoire.setStyle(sf::Text::Bold | sf::Text::Italic);
    texteVictoire.setFillColor(sf::Color::White);
    texteVictoire.setOutlineColor(sf::Color(20, 120, 20));
    texteVictoire.setOutlineThickness(3.f);
    texteVictoire.setPosition({ 340.f, 110.f });

    texteBravo.setString(
        "Bravo ! Vous avez gagne !\n"
        "Voici votre recompense !\n\n"
        "Appuie sur Espace pour recommencer.\n"
        "Appuie sur Echap pour revenir au menu."
    );
    texteBravo.setCharacterSize(24);
    texteBravo.setStyle(sf::Text::Bold);
    texteBravo.setFillColor(sf::Color::White);
    texteBravo.setOutlineColor(sf::Color::Black);
    texteBravo.setOutlineThickness(2.f);
    texteBravo.setPosition({ 180.f, 190.f });

    fabricationTitre.setString("Fabrication :");
    fabricationTitre.setCharacterSize(24);
    fabricationTitre.setStyle(sf::Text::Bold | sf::Text::Italic);
    fabricationTitre.setPosition({ 95.f, 215.f });
    fabricationTitre.setFillColor(sf::Color::Yellow);

    fabricationListe.setString("    - NAIM Oumayma\n    - RAOUZI Oumaima");
    fabricationListe.setCharacterSize(22);
    fabricationListe.setStyle(sf::Text::Bold | sf::Text::Italic);
    fabricationListe.setPosition({ 115.f, 255.f });
    fabricationListe.setFillColor(sf::Color(245, 245, 245));

    touchesTitre.setString("Utilisez les touches :");
    touchesTitre.setCharacterSize(24);
    touchesTitre.setStyle(sf::Text::Bold | sf::Text::Italic);
    touchesTitre.setPosition({ 95.f, 335.f });
    touchesTitre.setFillColor(sf::Color::Yellow);

    touchesListe.setString(
        "    - Espace ou Fleche Haut : sauter\n"
        "    - Fleche Bas : s'accroupir\n"
        "    - P : pause / reprendre\n"
        "    - Echap : retour au menu"
    );
    touchesListe.setCharacterSize(22);
    touchesListe.setStyle(sf::Text::Bold | sf::Text::Italic);
    touchesListe.setPosition({ 115.f, 375.f });
    touchesListe.setFillColor(sf::Color(245, 245, 245));

    finAPropos.setString("Bonne chance et essayez de battre votre meilleur score !");
    finAPropos.setCharacterSize(22);
    finAPropos.setStyle(sf::Text::Bold | sf::Text::Italic);
    finAPropos.setPosition({ 95.f, 500.f });
    finAPropos.setFillColor(sf::Color(255, 220, 120));

 
    textePauseTitre.setString("PAUSE");
    textePauseTitre.setCharacterSize(50);
    textePauseTitre.setStyle(sf::Text::Bold | sf::Text::Italic);
    textePauseTitre.setFillColor(sf::Color(255, 220, 70));
    textePauseTitre.setOutlineColor(sf::Color::Black);
    textePauseTitre.setOutlineThickness(3.f);

    sf::FloatRect bPauseTitre = textePauseTitre.getLocalBounds();
    textePauseTitre.setOrigin({
        bPauseTitre.position.x + bPauseTitre.size.x / 2.f,
        bPauseTitre.position.y + bPauseTitre.size.y / 2.f
        });
    textePauseTitre.setPosition({ 500.f, 190.f });

    textePauseInfo.setString(
        "Appuie sur P pour reprendre\n\n"
        "Appuie sur Echap pour revenir au menu"
    );
    textePauseInfo.setCharacterSize(22);
    textePauseInfo.setStyle(sf::Text::Bold);
    textePauseInfo.setFillColor(sf::Color::White);
    textePauseInfo.setOutlineColor(sf::Color::Black);
    textePauseInfo.setOutlineThickness(2.f);

    sf::FloatRect bPauseInfo = textePauseInfo.getLocalBounds();
    textePauseInfo.setOrigin({
        bPauseInfo.position.x + bPauseInfo.size.x / 2.f,
        bPauseInfo.position.y + bPauseInfo.size.y / 2.f
        });
    textePauseInfo.setPosition({ 500.f, 285.f });

    sol.setSize({ 1000.f, 0.f });
    sol.setFillColor(sf::Color::Transparent);
    sol.setPosition({ 0.f, 430.f });

    float xBarre = 760.f;
    float yBarre = 20.f;
    float largeurBarre = 220.f;
    float hauteurBarre = 22.f;
    float rayon = hauteurBarre / 2.f;

    // Fond gris
    barreTempsCentreFond.setSize({ largeurBarre - hauteurBarre, hauteurBarre });
    barreTempsCentreFond.setFillColor(sf::Color(180, 180, 180));
    barreTempsCentreFond.setPosition({ xBarre + rayon, yBarre });

    barreTempsGaucheFond.setRadius(rayon);
    barreTempsGaucheFond.setFillColor(sf::Color(180, 180, 180));
    barreTempsGaucheFond.setScale({ 1.f, 1.f });
    barreTempsGaucheFond.setPosition({ xBarre, yBarre });

    barreTempsDroiteFond.setRadius(rayon);
    barreTempsDroiteFond.setFillColor(sf::Color(180, 180, 180));
    barreTempsDroiteFond.setScale({ 1.f, 1.f });
    barreTempsDroiteFond.setPosition({ xBarre + largeurBarre - hauteurBarre, yBarre });

    // Barre verte
    barreTempsCentre.setSize({ largeurBarre - hauteurBarre, hauteurBarre });
    barreTempsCentre.setFillColor(sf::Color(50, 200, 70));
    barreTempsCentre.setPosition({ xBarre + rayon, yBarre });

    barreTempsGauche.setRadius(rayon);
    barreTempsGauche.setFillColor(sf::Color(50, 200, 70));
    barreTempsGauche.setScale({ 1.f, 1.f });
    barreTempsGauche.setPosition({ xBarre, yBarre });

    barreTempsDroite.setRadius(rayon);
    barreTempsDroite.setFillColor(sf::Color(50, 200, 70));
    barreTempsDroite.setScale({ 1.f, 1.f });
    barreTempsDroite.setPosition({ xBarre + largeurBarre - hauteurBarre, yBarre });

    titreChoix.setString("Choisissez votre personnage");
    titreChoix.setPosition({ 300.f, 60.f });
    titreChoix.setFillColor(sf::Color::White);
    titreChoix.setStyle(sf::Text::Bold);

    infoChoix.setString("Gauche / Droite pour changer - Entree pour valider");
    infoChoix.setPosition({ 180.f, 485.f });
    infoChoix.setFillColor(sf::Color::White);

    bool sautCharge = tamponSaut.loadFromFile("Son/jump.mp3");
    bool collisionCharge = tamponCollision.loadFromFile("Son/collision.mp3");
    bool victoireCharge = tamponVictoire.loadFromFile("Son/bravo.mp3");
    bool echecCharge = tamponEchec.loadFromFile("Son/echec.mp3");

    audioDisponible = sautCharge && collisionCharge && victoireCharge && echecCharge;

    if (audioDisponible)
    {
        sonSaut.setVolume(70.f);
        sonCollision.setVolume(80.f);
        sonVictoire.setVolume(85.f);
        sonEchec.setVolume(85.f);
    }

    if (musiqueFond.openFromFile("Son/font.mp3"))
    {
        musiqueFond.setLooping(true);
        musiqueFond.setVolume(35.f);
        musiqueFond.play();
    }

}

void Jeu::executer()
{
    sf::Clock horloge;
    while (fenetre.isOpen())
    {
        float dt = horloge.restart().asSeconds();
        gererEvenements();
        mettreAJour(dt);
        afficher();
    }
}

void Jeu::gererEvenements()
{
    while (const std::optional evenement = fenetre.pollEvent())
    {
        if (evenement->is<sf::Event::Closed>())
            fenetre.close();

        if (const auto* touche = evenement->getIf<sf::Event::KeyPressed>())
        {
            if (etat == Etat::Menu)
            {
                if (touche->code == sf::Keyboard::Key::Up)
                    menu.monter();
                else if (touche->code == sf::Keyboard::Key::Down)
                    menu.descendre();
                else if (touche->code == sf::Keyboard::Key::Enter)
                {
                    if (menu.getChoix() == 0)
                        etat = Etat::ChoixPersonnage;
                    else if (menu.getChoix() == 1)
                        etat = Etat::APropos;
                    else
                        fenetre.close();
                }
            }
            else if (etat == Etat::ChoixPersonnage)
            {
                if (touche->code == sf::Keyboard::Key::Left && choixPersonnage > 0)
                    choixPersonnage--;
                else if (touche->code == sf::Keyboard::Key::Right && choixPersonnage < 2)
                    choixPersonnage++;
                else if (touche->code == sf::Keyboard::Key::Enter)
                {
                    personnageSelectionne = choixPersonnage;
                    reinitialiserJeu();
                    etat = Etat::EnJeu;
                }
                else if (touche->code == sf::Keyboard::Key::Escape)
                {
                    etat = Etat::Menu;
                }
            }
            else if (etat == Etat::EnJeu)
            {
                if (touche->code == sf::Keyboard::Key::P)
                {
                    etat = Etat::Pause;
                }
                else if (touche->code == sf::Keyboard::Key::Space || touche->code == sf::Keyboard::Key::Up)
                {
                    joueur.relever();
                    if (joueur.sauter() && audioDisponible)
                        sonSaut.play();
                }
                else if (touche->code == sf::Keyboard::Key::Down)
                {
                    joueur.accroupir();
                }
                else if (touche->code == sf::Keyboard::Key::Escape)
                {
                    etat = Etat::Menu;
                }
            }
            else if (etat == Etat::Pause)
            {
                if (touche->code == sf::Keyboard::Key::P)
                {
                    etat = Etat::EnJeu;
                }
                else if (touche->code == sf::Keyboard::Key::Escape)
                {
                    etat = Etat::Menu;
                }
            }
            else if (etat == Etat::Fin || etat == Etat::Victoire)
            {
                if (touche->code == sf::Keyboard::Key::Space)
                {
                    reinitialiserJeu();
                    etat = Etat::EnJeu;
                }
                else if (touche->code == sf::Keyboard::Key::Escape)
                {
                    etat = Etat::Menu;
                }
            }
            else if (etat == Etat::APropos)
            {
                if (touche->code == sf::Keyboard::Key::Escape)
                    etat = Etat::Menu;
            }
        }

        if (const auto* toucheRelachee = evenement->getIf<sf::Event::KeyReleased>())
        {
            if ((etat == Etat::EnJeu || etat == Etat::Pause) &&
                toucheRelachee->code == sf::Keyboard::Key::Down)
            {
                joueur.relever();
            }
        }
    }
}

void Jeu::mettreAJour(float dt)
{
    decalageFond1 += 80.f * dt;
    if (decalageFond1 >= 1000.f)
        decalageFond1 = 0.f;

    if (etat == Etat::EnJeu)
        mettreAJourJeu(dt);
}

void Jeu::dessinerArrierePlan()
{
    if (backgroundCharge)
    {
        fond1.setPosition({ -decalageFond1, 0.f });
        fond2.setPosition({ 1000.f - decalageFond1, 0.f });
        fenetre.draw(fond1);
        fenetre.draw(fond2);
    }
    else
    {
        sf::RectangleShape fondSecours({ 1000.f, 550.f });
        fondSecours.setFillColor(sf::Color(120, 200, 255));
        fenetre.draw(fondSecours);
    }
}

void Jeu::mettreAJourJeu(float dt)
{
    if (invulnerable)
    {
        tempsInvulnerable += dt;
        if (tempsInvulnerable >= 1.0f)
        {
            invulnerable = false;
            tempsInvulnerable = 0.f;
        }
    }

    if (collisionEnCours)
    {
        tempsCollision += dt;
        joueur.mettreAJour(dt); 
        if (tempsCollision >= 0.4f) 
        {
            if (audioDisponible && !sonEchecJoue)
            {
                sonEchec.play();
                sonEchecJoue = true;
            }
            etat = Etat::Fin;
            collisionEnCours = false;
        }
        return; 
    }

    
    joueur.setPositionSol(SOL_Y);
    joueur.mettreAJour(dt);

    if (joueur.getPosition().y > 520.f)
    {
        if (audioDisponible && !sonEchecJoue)
        {
            sonEchec.play();
            sonEchecJoue = true;
        }
        etat = Etat::Fin;
        return;
    }

    tempsObstacle += dt;
    if (tempsObstacle >= delaiObstacle)
    {
        tempsObstacle = 0.f;
        creerObstacle();
    }

    tempsRestant -= dt;
    texteChrono.setString("Temps : " + 
        std::to_string(static_cast<int>(tempsRestant + 0.99f)));

    float largeurTotale = 220.f * (tempsRestant / tempsMax);
    if (largeurTotale < 0.f) largeurTotale = 0.f;

    float hauteurBarre = 22.f;
    float rayon = hauteurBarre / 2.f;
    float xBarre = 760.f;
    float yBarre = 20.f;

    // cacher par défaut
    barreTempsCentre.setSize({ 0.f, hauteurBarre });

    if (largeurTotale <= 0.f)
    {
        barreTempsCentre.setSize({ 0.f, hauteurBarre });
    }
    else if (largeurTotale <= hauteurBarre)
    {
        // petite boule seulement
        barreTempsGauche.setRadius(largeurTotale / 2.f);
        barreTempsGauche.setPosition({ xBarre, yBarre });
        barreTempsCentre.setSize({ 0.f, hauteurBarre });
    }
    else
    {
        barreTempsGauche.setRadius(rayon);
        barreTempsGauche.setPosition({ xBarre, yBarre });

        float largeurCentre = largeurTotale - hauteurBarre;
        if (largeurCentre < 0.f) largeurCentre = 0.f;

        barreTempsCentre.setSize({ largeurCentre, hauteurBarre });
        barreTempsCentre.setPosition({ xBarre + rayon, yBarre });

        barreTempsDroite.setRadius(rayon);
        barreTempsDroite.setPosition({ xBarre + largeurTotale - hauteurBarre, yBarre });
    }

    sf::Color couleurBarre;

    if (tempsRestant < 10.f)
        couleurBarre = sf::Color::Red;
    else if (tempsRestant < 20.f)
        couleurBarre = sf::Color(240, 180, 30);
    else
        couleurBarre = sf::Color(50, 200, 70);

    barreTempsCentre.setFillColor(couleurBarre);
    barreTempsGauche.setFillColor(couleurBarre);
    barreTempsDroite.setFillColor(couleurBarre);

    for (auto& obstacle : obstacles)
        obstacle.mettreAJour(dt);

    for (auto it = obstacles.begin(); it != obstacles.end();)
    {
        if (it->estHorsEcran())
        {
            it = obstacles.erase(it);
            score++;
        }
        else
            ++it;
    }

    texteScore.setString("Score : " + std::to_string(score));

    if (!invulnerable && verifierCollision())
    {
        nbTouches++;

        joueur.activerHurt();

        // 1er et 2e contact : son collision
        if (nbTouches < maxTouches)
        {
            if (audioDisponible)
                sonCollision.play();
        }

        // Mise a jour des coeurs
        if (nbTouches == 1)
        {
            if (coeur3) coeur3->setTexture(textureGrayHeart, true);
        }
        else if (nbTouches == 2)
        {
            if (coeur2) coeur2->setTexture(textureGrayHeart, true);
        }
        else if (nbTouches >= 3)
        {
            if (coeur1) coeur1->setTexture(textureGrayHeart, true);
        }

        invulnerable = true;
        tempsInvulnerable = 0.f;

        // 3e contact : son echec + game over
        if (nbTouches >= maxTouches)
        {
            if (audioDisponible && !sonEchecJoue)
            {
                sonEchec.play();
                sonEchecJoue = true;
            }

            etat = Etat::Fin;
            return;
        }
    }

    if (tempsRestant <= 0.f)
    {
        tempsRestant = 0.f;
        if (audioDisponible && !sonVictoireJoue)
        {
            sonVictoire.play();
            sonVictoireJoue = true;
        }
        etat = Etat::Victoire;
    }
}

void Jeu::creerObstacle()
{
    int choix = std::rand() % 13;

    TypeObstacle type;
    PositionObstacle position;

    switch (choix)
    {
    case 0:
        type = TypeObstacle::Fire;
        position = PositionObstacle::Bas;
        break;
    case 1:
        type = TypeObstacle::TreeWolf;
        position = PositionObstacle::Bas;
        break;
    case 2:
        type = TypeObstacle::CrystalWhite;
        position = PositionObstacle::Bas;
        break;
    case 3:
        type = TypeObstacle::TreeHuman;
        position = PositionObstacle::Bas;
        break;
    case 4:
        type = TypeObstacle::TotemUp;
        position = PositionObstacle::Bas;
        break;
    case 5:
        type = TypeObstacle::MegaTree;
        position = PositionObstacle::Bas;
        break;
    case 6:
        type = TypeObstacle::CrystalYellow;
        position = PositionObstacle::Bas;
        break;
    case 7:
        type = TypeObstacle::BranchesSnow;
        position = PositionObstacle::Haut;
        break;
    case 8:
        type = TypeObstacle::RockSpikes;
        position = PositionObstacle::Haut;
        break;
    case 9:
        type = TypeObstacle::GrassPlatform;
        position = PositionObstacle::Haut;
        break;
    case 10:
        type = TypeObstacle::WoodBranch;
        position = PositionObstacle::Haut;
        break;
    case 11:
        type = TypeObstacle::StonePlatform;
        position = PositionObstacle::Haut;
        break;
    default:
        type = TypeObstacle::Coconut;
        position = PositionObstacle::Haut;
        break;
    }

    obstacles.emplace_back(type, position, 1030.f, SOL_Y, 100.f, 330.f);
}

void Jeu::reinitialiserJeu()
{
    obstacles.clear();
    joueur.setTypePersonnage(personnageSelectionne);
    joueur.reinitialiser(180.f, SOL_Y);

    collisionEnCours = false;
    tempsCollision = 0.f;

    nbTouches = 0;
    invulnerable = false;
    tempsInvulnerable = 0.f;

    if (coeur1) coeur1->setTexture(textureRedHeart, true);
    if (coeur2) coeur2->setTexture(textureRedHeart, true);
    if (coeur3) coeur3->setTexture(textureRedHeart, true);

    score = 0;
    tempsObstacle = 0.f;
    tempsRestant = tempsMax;

    texteScore.setString("Score : 0");
    texteChrono.setString("Temps : 30");
    barreTemps.setSize({ 220.f, 22.f });
    barreTemps.setFillColor(sf::Color(50, 200, 70));
    sonVictoireJoue = false;
    sonEchecJoue = false;
}

bool Jeu::verifierCollision() const
{
    for (const auto& obstacle : obstacles)
    {
        if (joueur.getBornes().findIntersection(obstacle.getBornes()))
            return true;
    }
    return false;
}

void Jeu::dessinerBackgroundFin()
{
    sf::RectangleShape fond({ 1000.f, 550.f });
    fond.setFillColor(sf::Color(18, 60, 42));
    fenetre.draw(fond);

    for (int i = -250; i < 1300; i += 170)
    {
        sf::RectangleShape bande({ 320.f, 26.f });
        bande.setFillColor(sf::Color(80, 160, 95, 70));
        bande.setPosition({ static_cast<float>(i), -20.f });
        bande.setRotation(sf::degrees(35.f));
        fenetre.draw(bande);
    }
    sf::CircleShape halo1(95.f);
    halo1.setFillColor(sf::Color(220, 255, 170, 28));
    halo1.setPosition({ 40.f, 35.f });
    fenetre.draw(halo1);

    sf::CircleShape halo2(80.f);
    halo2.setFillColor(sf::Color(255, 245, 180, 20));
    halo2.setPosition({ 760.f, 55.f });
    fenetre.draw(halo2);

    sf::CircleShape halo3(60.f);
    halo3.setFillColor(sf::Color(255, 240, 150, 18));
    halo3.setPosition({ 430.f, 95.f });
    fenetre.draw(halo3);

    for (int i = 0; i < 35; i++)
    {
        float x = 40.f + (i * 27.f);
        float y = 40.f + ((i * 19) % 180);

        sf::CircleShape point(2.5f);
        point.setFillColor(sf::Color(255, 240, 180, 150));
        point.setPosition({ x, y });
        fenetre.draw(point);
    }

    sf::CircleShape collineFond1(260.f);
    collineFond1.setScale({ 2.4f, 0.60f });
    collineFond1.setFillColor(sf::Color(35, 90, 55));
    collineFond1.setPosition({ -180.f, 290.f });
    fenetre.draw(collineFond1);

    sf::CircleShape collineFond2(240.f);
    collineFond2.setScale({ 2.2f, 0.58f });
    collineFond2.setFillColor(sf::Color(30, 82, 52));
    collineFond2.setPosition({ 390.f, 310.f });
    fenetre.draw(collineFond2);

    sf::CircleShape collineAvant1(220.f);
    collineAvant1.setScale({ 2.2f, 0.52f });
    collineAvant1.setFillColor(sf::Color(55, 120, 68));
    collineAvant1.setPosition({ -120.f, 360.f });
    fenetre.draw(collineAvant1);

    sf::CircleShape collineAvant2(200.f);
    collineAvant2.setScale({ 2.0f, 0.48f });
    collineAvant2.setFillColor(sf::Color(48, 108, 62));
    collineAvant2.setPosition({ 520.f, 370.f });
    fenetre.draw(collineAvant2);

    sf::RectangleShape solDeco({ 1000.f, 95.f });
    solDeco.setFillColor(sf::Color(68, 105, 52));
    solDeco.setPosition({ 0.f, 455.f });
    fenetre.draw(solDeco);

    sf::RectangleShape herbe({ 1000.f, 20.f });
    herbe.setFillColor(sf::Color(150, 205, 85));
    herbe.setPosition({ 0.f, 448.f });
    fenetre.draw(herbe);

}

void Jeu::dessinerAPropos()
{
    dessinerBackgroundFin();

    // titre en haut
    sf::Text titre(policeGameOver, "A PROPOS", 54);
    titre.setStyle(sf::Text::Bold);
    titre.setFillColor(sf::Color::White);
    titre.setOutlineColor(sf::Color::Black);
    titre.setOutlineThickness(3.f);

    sf::FloatRect bt = titre.getLocalBounds();
    titre.setOrigin({ bt.position.x + bt.size.x / 2.f, 0.f });
    titre.setPosition({ 500.f, 10.f });
    fenetre.draw(titre);

    // introduction
    sf::Text intro(police,
        "Dans ce jeu de course, votre objectif est d'eviter les obstacles\n"
        "et de survivre jusqu'a la fin du chrono.",
        24);
    intro.setStyle(sf::Text::Bold | sf::Text::Italic);
    intro.setFillColor(sf::Color::White);
    intro.setOutlineColor(sf::Color::Black);
    intro.setOutlineThickness(2.f);

    sf::FloatRect bi = intro.getLocalBounds();
    intro.setOrigin({ bi.position.x + bi.size.x / 2.f, 0.f });
    intro.setPosition({ 500.f, 105.f });
    fenetre.draw(intro);

    // fabrication
    sf::Text fabTitre(police, "Fabrication :", 28);
    fabTitre.setStyle(sf::Text::Bold | sf::Text::Italic);
    fabTitre.setFillColor(sf::Color::Yellow);
    fabTitre.setOutlineColor(sf::Color::Black);
    fabTitre.setOutlineThickness(2.f);

    sf::FloatRect bfTitre = fabTitre.getLocalBounds();
    fabTitre.setOrigin({ bfTitre.position.x + bfTitre.size.x / 2.f, 0.f });
    fabTitre.setPosition({ 500.f, 170.f });
    fenetre.draw(fabTitre);

    sf::Text fabListe(police,
        "- NAIM Oumayma\n"
        "- RAOUZI Oumaima",
        24);
    fabListe.setStyle(sf::Text::Bold | sf::Text::Italic);
    fabListe.setFillColor(sf::Color::White);
    fabListe.setOutlineColor(sf::Color::Black);
    fabListe.setOutlineThickness(2.f);

    sf::FloatRect bfab = fabListe.getLocalBounds();
    fabListe.setOrigin({ bfab.position.x + bfab.size.x / 2.f, 0.f });
    fabListe.setPosition({ 500.f, 220.f });
    fenetre.draw(fabListe);

    // touches
    sf::Text touchesTitreLocal(police, "Utilisez les touches :", 28);
    touchesTitreLocal.setStyle(sf::Text::Bold | sf::Text::Italic);
    touchesTitreLocal.setFillColor(sf::Color::Yellow);
    touchesTitreLocal.setOutlineColor(sf::Color::Black);
    touchesTitreLocal.setOutlineThickness(2.f);

    sf::FloatRect btt = touchesTitreLocal.getLocalBounds();
    touchesTitreLocal.setOrigin({ btt.position.x + btt.size.x / 2.f, 0.f });
    touchesTitreLocal.setPosition({ 500.f, 290.f });
    fenetre.draw(touchesTitreLocal);

    sf::Text touchesListeLocal(police,
        "- Espace ou Fleche Haut : sauter\n"
        "- Fleche Bas : s'accroupir\n"
        "- P : pause / reprendre\n"
        "- Echap : retour au menu",
        23);
    touchesListeLocal.setStyle(sf::Text::Bold | sf::Text::Italic);
    touchesListeLocal.setFillColor(sf::Color::White);
    touchesListeLocal.setOutlineColor(sf::Color::Black);
    touchesListeLocal.setOutlineThickness(2.f);

    sf::FloatRect btl = touchesListeLocal.getLocalBounds();
    touchesListeLocal.setOrigin({ btl.position.x + btl.size.x / 2.f, 0.f });
    touchesListeLocal.setPosition({ 500.f, 325.f });
    fenetre.draw(touchesListeLocal);

    // texte bas
    sf::Text fin(police,
        "Bonne chance et essayez de battre votre meilleur score !",
        24);
    fin.setStyle(sf::Text::Bold | sf::Text::Italic);
    fin.setFillColor(sf::Color(255, 220, 120));
    fin.setOutlineColor(sf::Color::Black);
    fin.setOutlineThickness(2.f);

    sf::FloatRect bf = fin.getLocalBounds();
    fin.setOrigin({ bf.position.x + bf.size.x / 2.f, 0.f });
    fin.setPosition({ 500.f, 500.f });
    fenetre.draw(fin);
}

void Jeu::dessinerMiniPersonnage(float, float, int, bool)
{
}

void Jeu::dessinerChoixPersonnage()
{
    dessinerBackgroundFin();

    sf::Text titre(police, "Choisissez votre personnage", 34);
    titre.setStyle(sf::Text::Bold | sf::Text::Italic);
    titre.setFillColor(sf::Color::White);
    titre.setOutlineColor(sf::Color::Black);
    titre.setOutlineThickness(1.f);
    titre.setPosition({ 255.f, 35.f });

    sf::Text info(police, "Gauche / Droite pour changer - Entree pour valider", 22);
    info.setFillColor(sf::Color::White);
    info.setStyle(sf::Text::Bold);
    info.setOutlineColor(sf::Color::Black);
    info.setOutlineThickness(1.f);
    info.setPosition({ 180.f, 485.f });

    fenetre.draw(titre);
    fenetre.draw(info);

    sf::RectangleShape carte1({ 200.f, 250.f });
    carte1.setPosition({ 55.f, 135.f });
    carte1.setFillColor(sf::Color(255, 255, 255, 20));
    carte1.setOutlineThickness(4.f);
    carte1.setOutlineColor(choixPersonnage == 0 ? sf::Color(255, 220, 70) : sf::Color::White);

    sf::RectangleShape carte2({ 200.f, 250.f });
    carte2.setPosition({ 345.f, 135.f });
    carte2.setFillColor(sf::Color(255, 255, 255, 20));
    carte2.setOutlineThickness(4.f);
    carte2.setOutlineColor(choixPersonnage == 1 ? sf::Color(255, 220, 70) : sf::Color::White);

    sf::RectangleShape carte3({ 200.f, 250.f });
    carte3.setPosition({ 635.f, 135.f });
    carte3.setFillColor(sf::Color(255, 255, 255, 20));
    carte3.setOutlineThickness(4.f);
    carte3.setOutlineColor(choixPersonnage == 2 ? sf::Color(255, 220, 70) : sf::Color::White);

    fenetre.draw(carte1);
    fenetre.draw(carte2);
    fenetre.draw(carte3);

    if (spriteChoixChief)  fenetre.draw(*spriteChoixChief);
    if (spriteChoixFemale) fenetre.draw(*spriteChoixFemale);
    if (spriteChoixMale)   fenetre.draw(*spriteChoixMale);

    sf::Text nom1(police, "Chief", 24);
    nom1.setPosition({ 115.f, 405.f });
    nom1.setFillColor(sf::Color::White);
    nom1.setStyle(choixPersonnage == 0 ? sf::Text::Bold : sf::Text::Regular);

    sf::Text nom2(police, "Female", 24);
    nom2.setPosition({ 395.f, 405.f });
    nom2.setFillColor(sf::Color::White);
    nom2.setStyle(choixPersonnage == 1 ? sf::Text::Bold : sf::Text::Regular);

    sf::Text nom3(police, "Male", 24);
    nom3.setPosition({ 705.f, 405.f });
    nom3.setFillColor(sf::Color::White);
    nom3.setStyle(choixPersonnage == 2 ? sf::Text::Bold : sf::Text::Regular);

    fenetre.draw(nom1);
    fenetre.draw(nom2);
    fenetre.draw(nom3);
}

void Jeu::afficher()
{
    fenetre.clear();

    if (etat == Etat::Menu)
    {
        dessinerArrierePlan();
        menu.afficher(fenetre);
    }
    else if (etat == Etat::ChoixPersonnage)
    {
        dessinerChoixPersonnage();
    }
    else if (etat == Etat::EnJeu)
    {
        dessinerArrierePlan();

        for (auto& obstacle : obstacles)
            obstacle.dessiner(fenetre);

        joueur.dessiner(fenetre);

        fenetre.draw(texteScore);
        fenetre.draw(texteChrono);
        if (coeur1) fenetre.draw(*coeur1);
        if (coeur2) fenetre.draw(*coeur2);
        if (coeur3) fenetre.draw(*coeur3);
        fenetre.draw(barreTempsGaucheFond);
        fenetre.draw(barreTempsCentreFond);
        fenetre.draw(barreTempsDroiteFond);

        fenetre.draw(barreTempsGauche);
        fenetre.draw(barreTempsCentre);
        fenetre.draw(barreTempsDroite);
    }
    else if (etat == Etat::Pause)
    {
        dessinerArrierePlan();

        for (auto& obstacle : obstacles)
            obstacle.dessiner(fenetre);

        joueur.dessiner(fenetre);

        fenetre.draw(texteScore);
        fenetre.draw(texteChrono);
        if (coeur1) fenetre.draw(*coeur1);
        if (coeur2) fenetre.draw(*coeur2);
        if (coeur3) fenetre.draw(*coeur3);
        fenetre.draw(barreTempsGaucheFond);
        fenetre.draw(barreTempsCentreFond);
        fenetre.draw(barreTempsDroiteFond);

        fenetre.draw(barreTempsGauche);
        fenetre.draw(barreTempsCentre);
        fenetre.draw(barreTempsDroite);

        sf::RectangleShape voile({ 1000.f, 550.f });
        voile.setFillColor(sf::Color(0, 0, 0, 110));
        fenetre.draw(voile);

        sf::RectangleShape panneau({ 640.f, 230.f });
        panneau.setPosition({ 180.f, 140.f });
        panneau.setFillColor(sf::Color(20, 50, 30, 185));
        panneau.setOutlineThickness(3.f);
        panneau.setOutlineColor(sf::Color(255, 220, 70));
        fenetre.draw(panneau);

        fenetre.draw(textePauseTitre);
        fenetre.draw(textePauseInfo);
    }
    else if (etat == Etat::Fin)
    {
        dessinerBackgroundFin();

        sf::RectangleShape panneau({ 700.f, 300.f });
        panneau.setPosition({ 150.f, 105.f });
        panneau.setFillColor(sf::Color(20, 50, 30, 165));
        panneau.setOutlineThickness(3.f);
        panneau.setOutlineColor(sf::Color(196, 176, 110, 220));
        fenetre.draw(panneau);

        sf::RectangleShape ligneHaut({ 220.f, 8.f });
        ligneHaut.setPosition({ 390.f, 95.f });
        ligneHaut.setFillColor(sf::Color(196, 176, 110));
        fenetre.draw(ligneHaut);

        sf::RectangleShape ligneBas({ 320.f, 6.f });
        ligneBas.setPosition({ 340.f, 390.f });
        ligneBas.setFillColor(sf::Color(140, 120, 70));
        fenetre.draw(ligneBas);

        fenetre.draw(texteFin);

        sf::Text ligne1(police, "Oups !", 28);
        ligne1.setStyle(sf::Text::Bold | sf::Text::Italic);
        ligne1.setFillColor(sf::Color::White);
        ligne1.setOutlineColor(sf::Color::Black);
        ligne1.setOutlineThickness(2.f);
        sf::FloatRect b1 = ligne1.getLocalBounds();
        ligne1.setOrigin({ b1.position.x + b1.size.x / 2.f, 0.f });
        ligne1.setPosition({ 500.f, 220.f });

        sf::Text ligne2(police, "Tu t'es pris un obstacle...", 28);
        ligne2.setStyle(sf::Text::Bold | sf::Text::Italic);
        ligne2.setFillColor(sf::Color::White);
        ligne2.setOutlineColor(sf::Color::Black);
        ligne2.setOutlineThickness(2.f);
        sf::FloatRect b2 = ligne2.getLocalBounds();
        ligne2.setOrigin({ b2.position.x + b2.size.x / 2.f, 0.f });
        ligne2.setPosition({ 500.f, 260.f });

        sf::Text ligne3(police, "Essaie encore, tu peux faire mieux !", 28);
        ligne3.setStyle(sf::Text::Bold | sf::Text::Italic);
        ligne3.setFillColor(sf::Color::White);
        ligne3.setOutlineColor(sf::Color::Black);
        ligne3.setOutlineThickness(2.f);
        sf::FloatRect b3 = ligne3.getLocalBounds();
        ligne3.setOrigin({ b3.position.x + b3.size.x / 2.f, 0.f });
        ligne3.setPosition({ 500.f, 300.f });

        fenetre.draw(ligne1);
        fenetre.draw(ligne2);
        fenetre.draw(ligne3);

        sf::Text texteBas(police, "ESPACE pour recommencer - ECHAP pour revenir au menu", 24);
        texteBas.setStyle(sf::Text::Bold | sf::Text::Italic);
        texteBas.setFillColor(sf::Color(225, 235, 210));
        texteBas.setOutlineColor(sf::Color(20, 35, 18));
        texteBas.setOutlineThickness(2.f);

        sf::FloatRect bBas = texteBas.getLocalBounds();
        texteBas.setOrigin({ bBas.position.x + bBas.size.x / 2.f, 0.f });
        texteBas.setPosition({ 500.f, 470.f });

        fenetre.draw(texteBas);
    }
    else if (etat == Etat::Victoire)
    {
        dessinerBackgroundFin();

        sf::RectangleShape panneau({ 700.f, 300.f });
        panneau.setPosition({ 150.f, 105.f });
        panneau.setFillColor(sf::Color(20, 50, 30, 165));
        panneau.setOutlineThickness(3.f);
        panneau.setOutlineColor(sf::Color(140, 220, 120, 220));
        fenetre.draw(panneau);

        sf::RectangleShape ligneHaut({ 220.f, 8.f });
        ligneHaut.setPosition({ 390.f, 95.f });
        ligneHaut.setFillColor(sf::Color(140, 220, 120));
        fenetre.draw(ligneHaut);

        sf::RectangleShape ligneBas({ 320.f, 6.f });
        ligneBas.setPosition({ 340.f, 390.f });
        ligneBas.setFillColor(sf::Color(110, 190, 90));
        fenetre.draw(ligneBas);

        // titre VICTOIRE centré
        sf::Text titreVictoire(policeGameOver, "VICTOIRE !", 60);
        titreVictoire.setStyle(sf::Text::Bold);
        titreVictoire.setFillColor(sf::Color::White);
     
      

        sf::FloatRect bTitre = titreVictoire.getLocalBounds();
        titreVictoire.setOrigin({ bTitre.position.x + bTitre.size.x / 2.f, 0.f });
        titreVictoire.setPosition({ 500.f, 120.f });

        fenetre.draw(titreVictoire);

        // lignes du milieu centrées
        sf::Text ligne1(police, "Bravo ! Vous avez gagne !", 28);
        ligne1.setStyle(sf::Text::Bold | sf::Text::Italic);
        ligne1.setFillColor(sf::Color::White);
        ligne1.setOutlineColor(sf::Color::Black);
        ligne1.setOutlineThickness(2.f);
        sf::FloatRect b1 = ligne1.getLocalBounds();
        ligne1.setOrigin({ b1.position.x + b1.size.x / 2.f, 0.f });
        ligne1.setPosition({ 500.f, 220.f });

        sf::Text ligne2(police, "Voici votre recompense !", 28);
        ligne2.setStyle(sf::Text::Bold | sf::Text::Italic);
        ligne2.setFillColor(sf::Color::White);
        ligne2.setOutlineColor(sf::Color::Black);
        ligne2.setOutlineThickness(2.f);
        sf::FloatRect b2 = ligne2.getLocalBounds();
        ligne2.setOrigin({ b2.position.x + b2.size.x / 2.f, 0.f });
        ligne2.setPosition({ 500.f, 260.f });

        sf::Text ligne3(police, "Tu as termine la course avec succes !", 28);
        ligne3.setStyle(sf::Text::Bold | sf::Text::Italic);
        ligne3.setFillColor(sf::Color::White);
        ligne3.setOutlineColor(sf::Color::Black);
        ligne3.setOutlineThickness(2.f);
        sf::FloatRect b3 = ligne3.getLocalBounds();
        ligne3.setOrigin({ b3.position.x + b3.size.x / 2.f, 0.f });
        ligne3.setPosition({ 500.f, 300.f });

        fenetre.draw(ligne1);
        fenetre.draw(ligne2);
        fenetre.draw(ligne3);

        // texte bas
        sf::Text texteBas(police, "ESPACE pour recommencer - ECHAP pour revenir au menu", 24);
        texteBas.setStyle(sf::Text::Bold | sf::Text::Italic);
        texteBas.setFillColor(sf::Color(225, 235, 210));
        texteBas.setOutlineColor(sf::Color::White);
        texteBas.setOutlineThickness(2.f);

        sf::FloatRect bBas = texteBas.getLocalBounds();
        texteBas.setOrigin({ bBas.position.x + bBas.size.x / 2.f, 0.f });
        texteBas.setPosition({ 500.f, 470.f });

        fenetre.draw(texteBas);
        }
    else if (etat == Etat::APropos)
    {
        dessinerAPropos();
    }

    fenetre.display();
}