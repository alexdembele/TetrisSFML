#include "game.hpp"
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

    //chargement graphisme
    
    if(!PieceTexture_.loadFromFile("../Projet/images/tiles.png"))
      printf("Erreur chargement\n");
    if(!backgroundTexture_.loadFromFile("../Projet/images/background.png"))
      printf("Erreur chargement\n");
    if(!FrameTexture_.loadFromFile("../Projet/images/frame.png"))
      printf("Erreur chargement\n");
    sf::Sprite backgroundSprite_(backgroundTexture_);
    sf::Sprite PieceSprite_(PieceTexture_);
    sf::Sprite FrameSprite_(FrameTexture_);
    scaleToMinSize(backgroundSprite_,1900,1100);
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
    //eclair
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) 
    {
        
    }

    //supprime ligne
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) 
    {
        
    }
    //supprime colonne
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) 
    {
        
    }
}

bool Game::updateGame(float timer)
{
    bool tick=false;
    
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

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite backgroundSprite_(backgroundTexture_);
    sf::Sprite PieceSprite_(PieceTexture_);
    sf::Sprite FrameSprite_(FrameTexture_);
    scaleToMinSize(backgroundSprite_,1900,1100);
    target.clear(Color::Black);    
    target.draw(backgroundSprite_);
          
    // affichage grille
    for (int i=0;i<hauteur;i++)
     for (int j=0;j<largeur;j++)
       {
         if (grille.grille[i][j]==0) continue;
         PieceSprite_.setTextureRect(IntRect(grille.grille[i][j]*18,0,18,18));
         PieceSprite_.setPosition(j*18,i*18);
         PieceSprite_.move(28,31); //offset
         target.draw(PieceSprite_);
       }
   
    //affichage pièce en déplacement
    for (int i=0;i<4;i++)
      {
        PieceSprite_.setTextureRect(IntRect(piece.color*18,0,18,18));
        PieceSprite_.setPosition(piece.courant[i].x*18,piece.courant[i].y*18);
        PieceSprite_.move(28,31); //offset
        target.draw(PieceSprite_);
        

      }
      target.draw(FrameSprite_);
      FrameSprite_.move(Vector2f(450.f,0));
      target.draw(FrameSprite_);
}