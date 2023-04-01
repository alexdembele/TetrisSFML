#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <vector>
#include <time.h>
#include<sstream>
#include<iostream>
#include"utils.hpp"
#include"piece.hpp"
#include"grille.hpp"
#include"game.hpp"



//TRICKY TOWER
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{int x,y;} a[4], b[4];

int figures[7][4] =
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};
sf::Packet& operator <<(sf::Packet& packet, const Game& game)
{
     for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        packet <<  game.grille.grille[i][j];
      }
     
    }
    return packet ;
}

sf::Packet& operator >>(sf::Packet& packet, Game& game)
{
    for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        packet >>  game.grille.grille[i][j];
      }
     
    }
    
    return packet ;
}



int main()
{
    srand(time(0));     
    //chargement graphisme
    RenderWindow window(VideoMode(1800, 1000), "The Game!");

    
    //definition des parametres de jeu
    
    /* Reseau
    sf::TcpSocket socket;
    //socket.setBlocking(false);
    sf::Socket::Status status = socket.connect("147.250.226.73",52000);
    if(status != sf::Socket::Done)
    {
      printf("Erreur connection\n");
    }
    sf::Packet packet;
    std::string data ="Yousk2";
    
    std::cout << data<< std::endl;
    packet <<data ;
    socket.send(packet);
    */


    
    Clock clock;

    //TEST
    //definition de la grille
    
    Grille Tertest;
    
    //definition de la piece
   
    Piece piecTest;

    //definition de la partie
    Game myGame(Tertest,piecTest,true);
    //definition temps
    float temps=0;
    
    std::cout << sf::IpAddress::getPublicAddress( ) << "\n";
  
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        
        temps+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            
              myGame.commande(e);
        }

    
    /*
    packet << myGame;
    socket.send(packet);*/
    
    //printf("Reçu : %s",data);
    if (not(myGame.end)&&!myGame.afficheMenu)
    {
      if (myGame.updateGame(temps) )
      {
       temps=0;
       
      }
    }
    
    
    myGame.levelup();
    myGame.endGame();
    
   
    window.draw(myGame);
    
    window.display();
    }

    return 0;
}
