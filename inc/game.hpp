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

using namespace sf;


class Grille;
class Piece;
class Game : public sf::Drawable
{

    public:
        Grille grille;
        Piece piece;
        int direction;
        bool rotate;
        float delai;
        float tempsTampon;
        float tempsTmp;
        //graphisme
        sf::Texture backgroundTexture_;
        sf::Texture PieceTexture_;
        sf::Texture FrameTexture_;
        

    public:
        Game(Grille grille_, Piece piece_);
        void commande(Event clavier); // entree clavier
        bool updateGame(float timer); // avancement du jeu
        void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
        
        

};
#endif
