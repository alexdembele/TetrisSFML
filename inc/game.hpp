#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "grille.hpp"
#include "utils.hpp"
#include <cmath>
#include <vector>
#include <time.h>
#include<sstream>
#include<iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Network.hpp>

using namespace sf;


class Grille;
class Piece;
class Game : public sf::Drawable
{

    public:
        Grille grille;
        Piece piece;
        Piece Preview;
        int direction;
        bool rotate;
        float delai;
        float delais;
        float tempsTampon;
        float tempsTmp;
        bool end;
        bool local;
        int score;
        int level;
        bool afficheMenu;
        //graphisme
        sf::Texture backgroundTexture_;
        sf::Texture PieceTexture_;
        sf::Texture FrameTexture_;
        sf::Texture GameOverTexture_;
        sf::Texture eclairTexture_;
        sf::Texture interditTexture_;
        sf::Texture asteroideTexture_;
        sf::Texture menuTexture_;
        sf::Font policeTexte;

        //pouvoir speciaux
        bool eclairReady;
        int eclairTimer;
        bool ligneReady;
        int ligneTimer;
        bool colonneReady;
        int colonneTimer;
        bool asteroideReady;
        int asteroideTimer;

        

        

    public:
        Game(Grille grille_, Piece piece_, bool localite);
        void commande(Event clavier); // entree clavier
        bool updateGame(float timer); // avancement du jeu
        void endGame();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
        void levelup();
        
        

};

#endif
