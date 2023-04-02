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
   
    Preview=piece_;
    piece=Piece();
    direction=0;
    rotate=0;
    delai=0.3;
    tempsTampon=0;
    end=false;
    local=localite;
    score=0;
    level=1;
    afficheMenu=true;
    eclairTimer=100000;
    eclairReady=true;
    asteroideTimer=500000;
    asteroideReady=true;
    ligneTimer=100000;
    ligneReady=true;
    colonneTimer=200000;
    colonneReady=true;

    //chargement graphisme
    
    if(!PieceTexture_.loadFromFile("../Projet/images/tiles.png"))
      printf("Erreur chargement\n");
    if(!backgroundTexture_.loadFromFile("../Projet/images/background.png"))
      printf("Erreur chargement\n");
    if(!FrameTexture_.loadFromFile("../Projet/images/frame.png"))
      printf("Erreur chargement\n");
    if(!GameOverTexture_.loadFromFile("../Projet/images/gameOver.png"))
      printf("Erreur chargement\n");
    if(!eclairTexture_.loadFromFile("../Projet/images/eclair.png"))
      printf("Erreur chargement\n");
    if(!asteroideTexture_.loadFromFile("../Projet/images/asteroide.png"))
      printf("Erreur chargement\n");
    if(!interditTexture_.loadFromFile("../Projet/images/interdit.png"))
      printf("Erreur chargement\n");
    if(!menuTexture_.loadFromFile("../Projet/images/menu.jpg"))
      printf("Erreur chargement\n");
    
    sf::Sprite backgroundSprite_(backgroundTexture_);
    sf::Sprite PieceSprite_(PieceTexture_);
    sf::Sprite FrameSprite_(FrameTexture_);
    sf::Sprite GameOverSprite_(GameOverTexture_);
    sf::Sprite eclairSprite_(eclairTexture_);
    sf::Sprite asteroideSprite_(asteroideTexture_);
    sf::Sprite colonneSprite_(interditTexture_);
    sf::Sprite ligneSprite_(interditTexture_);
    sf::Sprite menuSprite_(menuTexture_);

    
    
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
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) 
    {
      afficheMenu=false;
    }
    if (clavier.type == Event::KeyPressed)
              if (clavier.key.code==Keyboard::Up) rotate=true;
              else if (clavier.key.code==Keyboard::Left) direction=-1;
              else if (clavier.key.code==Keyboard::Right) direction=1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
    {
        delais=0.05;
    }
    //eclair
    
    
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)&&eclairReady) 
    {
        grille.eclairTombe();
        eclairTimer= 100000 ;
        eclairReady=false;
    }
    
    //supprime ligne
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)&&ligneReady) 
    {
        grille.suppLigne();
        ligneTimer=100000;
        ligneReady=false;
        
    }
    //supprime colonne
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)&&colonneReady) 
    {
        grille.suppColonne();
        colonneTimer=200000;
        colonneReady=false;
        
    }
    //meteorite
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)&&asteroideReady) 
    {
        grille.asteroideTombe();
        asteroideTimer=500000;
        asteroideReady=false;
        
    }
}

bool Game::updateGame(float timer)
{
    bool tick=false;
    
    if (eclairTimer>0)
    {
      eclairTimer-=1;
      if (eclairTimer==0)
      {
        eclairReady=true;
      }
    }

    if (asteroideTimer>0)
    {
      asteroideTimer-=1;
      if (asteroideTimer==0)
      {
        asteroideReady=true;
      }
    }

    if (ligneTimer>0)
    {
      ligneTimer-=1;
      if (ligneTimer==0)
      {
        ligneReady=true;
      }
    }

    if (colonneTimer>0)
    {
      colonneTimer-=1;
      if (colonneTimer==0)
      {
        colonneReady=true;
      }
    }
    
    if((timer-tempsTampon)>0.05) // This ensures that the game piece moves at a fixed interval and avoids excessively fast gameplay.
    {
        
        piece.move(direction,grille);
        
        tempsTampon=timer;
    }
    if((timer-tempsTmp)>delai/2) //This ensures that the game piece can only be rotated every so often, which adds an additional element of strategy to the gameplay.
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
            piece=Preview;
            Preview.reset();
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
    sf::Sprite eclairSprite_(eclairTexture_);
    sf::Sprite asteroideSprite_(asteroideTexture_);
    sf::Sprite colonneSprite_(interditTexture_);
    sf::Sprite ligneSprite_(interditTexture_);
    sf::Sprite menuSprite_(menuTexture_);
    setOriginToCenter(ligneSprite_);
    setOriginToCenter(colonneSprite_);
    sf::Text textScore;
    sf::Text textMenu;
    
    textScore.setFont(policeTexte);
    textMenu.setFont(policeTexte);
    
    textScore.setCharacterSize(24);
    textScore.setFillColor(sf::Color::Magenta);
    textMenu.setCharacterSize(40);
    textMenu.setFillColor(sf::Color::Black);
    
    std::string Scores=std::to_string(score);
    std::string Levels=std::to_string(level);
    textScore.setString("Score:"+Scores+"   Level:"+Levels);
    textScore.move(0, 400.f);
    if(!local) textScore.move(450.f,0);
    textMenu.setString("Press P to play Solo\n");


    /* Affichage des commandes pour utiliser les bonus */
    
    //eclair 
    sf::Text Bonus_eclair;
    Bonus_eclair.setCharacterSize(18);
    Bonus_eclair.setFont(policeTexte);
    Bonus_eclair.setFillColor(sf::Color::Yellow);    
    Bonus_eclair.move(0, 550.f);

    //asteroide
    sf::Text Bonus_asteroide;
    Bonus_asteroide.setCharacterSize(18);
    Bonus_asteroide.setFont(policeTexte);
    Bonus_asteroide.setFillColor(sf::Color::Black);
    Bonus_asteroide.move(150, 550.f);

    //ligne
    sf::Text Bonus_ligne;
    Bonus_ligne.setCharacterSize(18);
    Bonus_ligne.setFont(policeTexte);
    Bonus_ligne.setFillColor(sf::Color::Green);
    Bonus_ligne.move(150, 700.f);

    //colonne
     sf::Text Bonus_colonne;
    Bonus_colonne.setCharacterSize(18);
    Bonus_colonne.setFont(policeTexte);
    Bonus_colonne.setFillColor(sf::Color::Magenta);
    Bonus_colonne.move(0, 700.f);
    
    
    
    if (local) target.clear(Color::Black);  
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
         if(!local) PieceSprite_.move(450.f,0);
         target.draw(PieceSprite_);
       }
   
    //affichage pièce en déplacement
    if(local)
    {

    
    for (int i=0;i<4;i++)
      {
        PieceSprite_.setTextureRect(IntRect(piece.color*18,0,18,18));
        PieceSprite_.setPosition(piece.courant[i].x*18,piece.courant[i].y*18);
        PieceSprite_.move(28,31); //offset
        if(!local) PieceSprite_.move(450.f,0);
        target.draw(PieceSprite_);
      }
    }
    //affichage Preview
    if (local)
    {

    
      for (int i=0;i<4;i++)
      {
        PieceSprite_.setTextureRect(IntRect(Preview.color*18,0,18,18));
        PieceSprite_.setPosition(Preview.courant[i].x*18,Preview.courant[i].y*18);
        PieceSprite_.move(170,31); //offset
        target.draw(PieceSprite_);
      }
    }

      if (local)
      {
      target.draw(FrameSprite_);
      FrameSprite_.move(Vector2f(450.f,0));
      target.draw(FrameSprite_);
      target.draw(textScore);
      //eclair
      eclairSprite_.move(Vector2f(0,450.f));
      eclairSprite_.scale(0.1f,0.07f);

      if (eclairReady)
      {
        target.draw(eclairSprite_);
        Bonus_eclair.setString("Press E \nfor lightning");
      }
      else
      {
        int loading_eclair;
        loading_eclair = round(100 - eclairTimer/1000);
        std::string s_loading_eclair = std::to_string(loading_eclair);
        Bonus_eclair.setString("Lightning\n"+s_loading_eclair+"% ready");
      }
      target.draw(Bonus_eclair);
      
      //asteroide
      asteroideSprite_.move(Vector2f(125.f,450.f));
      asteroideSprite_.scale(0.3f,0.3f);
      if (asteroideReady) 
      {
        target.draw(asteroideSprite_);
        Bonus_asteroide.setString("Press M \nfor Asteroid");
      }
      else
      { 
        int loading_asteroid;
        loading_asteroid = round(100 - asteroideTimer/5000);
        std::string s_loading_asteroid = std::to_string(loading_asteroid); 
        Bonus_asteroide.setString("Asteroid\n"+s_loading_asteroid+"% ready");
      }
      target.draw(Bonus_asteroide) ;

      //ligne
      ligneSprite_.move(Vector2f(160.f,650.f));
      ligneSprite_.rotate(-45);
      ligneSprite_.scale(0.1f,0.1f);
       if(ligneReady) 
      {
        target.draw(ligneSprite_);
        Bonus_ligne.setString("Press L \nfor Line-zap");
      }
      else
      {
        int loading_ligne;
        loading_ligne = round(100 - ligneTimer/1000);
        std::string s_loading_ligne = std::to_string(loading_ligne);
        Bonus_ligne.setString("LineZap\n"+s_loading_ligne+"% ready");
      }
      target.draw(Bonus_ligne);
            
      //colonne
      colonneSprite_.move(Vector2f(50.f,650.f));
      colonneSprite_.rotate(45);
      colonneSprite_.scale(0.1f,0.1f);
       if(colonneReady) 
       {
        target.draw(colonneSprite_);
        Bonus_colonne.setString("Press C \nfor Column-zap");
       }
       else
       {
        int loading_column;
        loading_column = round(100 - colonneTimer/2000);
        std::string s_loading_colonne = std::to_string(loading_column);
        Bonus_colonne.setString("ColumnZap\n"+s_loading_colonne+"% ready");
       }
       target.draw(Bonus_colonne);

      }
      target.draw(textScore);
      

      GameOverSprite_.scale(1.2f, 2.05f);
      if(end)
      {
        if(!local) GameOverSprite_.move(450.f,0);
        target.draw(GameOverSprite_);
      }

      if(local&&afficheMenu)
      {
      
        scaleToMaxSize(menuSprite_,1900,1100);
        target.draw(menuSprite_);
        target.draw(textMenu);
    
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