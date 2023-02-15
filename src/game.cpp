#include "game.hpp"
#include <SFML/System.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "piece.hpp"
#include "grille.hpp"
#include "utils.hpp"
#include <cmath>
#include <vector>
#include <time.h>
#include<sstream>
#include<iostream>

Game::Game(Grille grille_, Piece piece_)
{
    grille=grille_;
    piece=piece_;
    direction=0;
    rotate=0;
    delai=0.3;
}

void Game::commande(Event clavier)
{
    rotate=0;
    direction=0;
    delai=0.3;
    Event e;
    if (clavier.type == Event::KeyPressed)
              if (clavier.key.code==Keyboard::Up) rotate=true;
              else if (clavier.key.code==Keyboard::Left) direction=-1;
              else if (clavier.key.code==Keyboard::Right) direction=1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
    {
        delai=0.05;
    }
}

bool Game::updateGame(float timer)
{
    bool tick=false;
    piece.move(direction,grille);
    if(rotate)
    {
        piece.rotate(grille);
    }

    if(timer>delai)
    {
        piece.descend();
        if(!piece.occupe(grille))
        {
            grille.ajoutePiece(piece);
            piece.reset();
        }
        tick=true;
    }
    grille.clearLine();
    return tick;
}