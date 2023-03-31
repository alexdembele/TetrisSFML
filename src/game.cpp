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


Game::Game(Grille grille_, Piece piece_,bool localite)
{
    grille=grille_;
    piece=piece_;
    direction=0;
    rotate=0;
    delai=0.3;
    tempsTampon=0;
    end=false;
    local=localite;
    score=0;
    level=1;
    eclairTimer=1000;
    eclairReady=false;

    //chargement graphisme
    
    if(!PieceTexture_.loadFromFile("../Projet/images/tiles.png"))
      printf("Erreur chargement\n");
    if(!backgroundTexture_.loadFromFile("../Projet/images/background.png"))
      printf("Erreur chargement\n");
    if(!FrameTexture_.loadFromFile("../Projet/images/frame.png"))
      printf("Erreur chargement\n");
    if(!GameOverTexture_.loadFromFile("../Projet/images/gameOver.png"))
      printf("Erreur chargement\n");
    sf::Sprite backgroundSprite_(backgroundTexture_);
    sf::Sprite PieceSprite_(PieceTexture_);
    sf::Sprite FrameSprite_(FrameTexture_);
    sf::Sprite GameOverSprite_(GameOverTexture_);
    
    if (!policeTexte.loadFromFile("../Projet/Fredoka-Bold.ttf"))
    {
      printf("Erreur chargement\n");
    }
    scaleToMinSize(backgroundSprite_,1900,1100);
    scaleToMinSize(GameOverSprite_,1900,1100);
    
}

void Game::commande(Event clavier)
{
    rotate=0;
    direction=0;
    delais=delai;
    if (clavier.type == Event::KeyPressed)
              if (clavier.key.code==Keyboard::Up) rotate=true;
              else if (clavier.key.code==Keyboard::Left) direction=-1;
              else if (clavier.key.code==Keyboard::Right) direction=1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
    {
        delais=0.05;
    }
    //eclair
    if (eclairTimer>0)
    {
      eclairTimer-=1;
      if (eclairTimer==0)
      {
        eclairReady=true;
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)&&eclairReady) 
    {
        eclairTimer=1000;
        eclairReady=false;
    }
    
    //supprime ligne
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) 
    {
        
    }
    //supprime colonne
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) 
    {
        
    }
    //meteorite
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) 
    {
        
    }
}

bool Game::updateGame(float timer)
{
    bool tick=false;
    
    
    if((timer-tempsTampon)>0.05)
    {
        
        piece.move(direction,grille);
        
        tempsTampon=timer;
    }
    if((timer-tempsTmp)>delai/2)
    {
        if(rotate)
        {
            piece.rotate(grille);
        }
        tempsTmp=timer;
    }
    if(timer>delais)
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
    score+=level*grille.clearLine();
    return tick;

    
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite backgroundSprite_(backgroundTexture_);
    sf::Sprite PieceSprite_(PieceTexture_);
    sf::Sprite FrameSprite_(FrameTexture_);
    sf::Sprite GameOverSprite_(GameOverTexture_);
    sf::Text textScore;
    textScore.setFont(policeTexte);
    textScore.setCharacterSize(24);
    textScore.setFillColor(sf::Color::Magenta);
    std::string Scores=std::to_string(score);
    std::string Levels=std::to_string(level);
    textScore.setString("Score:"+Scores+"   Level:"+Levels);
    textScore.move(0, 400.f);
    
    
    
    target.clear(Color::Black);  
    if (local)
    {
    scaleToMinSize(backgroundSprite_,1900,1100);
    target.draw(backgroundSprite_);
    }
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

      if (local)
      {
      target.draw(FrameSprite_);
      FrameSprite_.move(Vector2f(450.f,0));
      target.draw(FrameSprite_);
      }
      target.draw(textScore);
      GameOverSprite_.scale(1.f, 2.05f);
      if(end)
      {
        target.draw(GameOverSprite_);
      }
}

void Game::endGame()
{
  for (int j=0; j<largeur; j++)
  {
    if (grille.grille[1][j]!=0)
    {
      
      end=true;
    }
  } 
  
}

void Game::levelup()
{
  if (level<60)
  {
    while (score>(1000+level*200)*level)
    {
      level+=1;
      if (level<=10)
        {
          delai-=0.02;
        }
      else if (level<=15)
        {
          delai-=0.01;
        }
      else
      {

      }
    }
  }
  
  

}