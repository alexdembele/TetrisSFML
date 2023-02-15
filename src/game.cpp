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
#include <SFML/Graphics.hpp>

Game::Game(Grille grille_, Piece piece_)
{
    grille=grille_;
    piece=piece_;
    direction=0;
    rotate=0;
    delai=0.3;
    tempsTampon=0;
}

void Game::commande(Event clavier)
{
    rotate=0;
    direction=0;
    delai=0.3;
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
    printf("%f:%f\n",timer,tempsTampon);
    if((timer-tempsTampon)>0.07)
    {
        
        piece.move(direction,grille);
        
        tempsTampon=timer;
    }
    if((timer-tempsTmp)>0.1)
    {
        if(rotate)
        {
            piece.rotate(grille);
        }
        tempsTmp=timer;
    }
    if(timer>delai)
    {
        piece.descend();
        if(!piece.occupe(grille))
        {
            grille.ajoutePiece(piece);
            piece.reset();
        }
        tempsTampon=0;
        tempsTmp=0;
        tick=true;
    }
    grille.clearLine();
    return tick;

    
}