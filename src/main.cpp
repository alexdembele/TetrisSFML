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

//piece et commande avec borne => def protocole
sf::Packet& operator <<(sf::Packet& packet, const Game& game)
{
    std::int16_t buffer;
     for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        buffer=game.grille.grille[i][j];
        packet <<  buffer;
        std::cout<<buffer<<";";
      }
     
    }
    std::cout<<"\n";
    return packet ;
}

sf::Packet& operator >>(sf::Packet& packet, Game& game)
{
  std::int16_t buffer;
    for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {

        packet >> buffer;
        game.grille.grille[i][j]=buffer;
        
        
      }
     
    }
    
    return packet ;
}



int main()
{
    srand(time(0));     
    //chargement graphisme
    RenderWindow window(VideoMode(1800, 1000), "The Game!");
    
  
    
     //Reseau
    sf::TcpSocket socket;
    //socket.setBlocking(false);
    sf::Socket::Status status = socket.connect("147.250.225.105",52000);
    if(status != sf::Socket::Done)
    {
      printf("Erreur connection\n");
    }
    sf::Packet packet;
    std::string data ="Yousk2";
    std::string datta="Yousk1";
    
    
    std::cout << data<< std::endl;
    packet <<data ;
    packet <<datta;
    
    socket.send(packet);
    


    
    Clock clock;

    //definition de la grille
    
    Grille Tertest;
    Grille grilleReseau;
    
    //definition de la piece
   
    Piece piecTest;
    Piece pieceReseau;

    //definition de la partie
    Game myGame(Tertest,piecTest,true);
    Game gameReseau(grilleReseau,pieceReseau,false);

    //definition temps
    float temps=0;
    float tempsReseau=0;
    
    std::cout << sf::IpAddress::getPublicAddress( ) << "\n";
  
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        
        temps+=time;
        tempsReseau+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            
              myGame.commande(e);
        }

    
    socket.setBlocking(false);
    //envoie grille
    /*for (int i=0; i<20; i++)
      {
      for (int j=0;j<10;j++)
      {
        std::cout <<  myGame.grille.grille[i][j]<<";";
      }
     
    }*/
    
   
    
    
    
    //printf("Reçu : %s",data);
    if (not(myGame.end)&&!myGame.afficheMenu)
    {
      if (myGame.updateGame(temps) )
      {
       temps=0;
       
       
      }
    }
    if(tempsReseau>1)
    {
    tempsReseau=0;
    packet.clear();
    packet << myGame;
    //packet <<"Yousk1";
    socket.send(packet);
    //reception grille
    packet.clear();
    socket.receive(packet);
    //std::cout <<packet<<"\n";
    packet>>gameReseau;
    packet.clear();
    }
    
    myGame.levelup();
    myGame.endGame();
    
   
    window.draw(myGame);
    window.draw(gameReseau);
    
    window.display();
    }

    return 0;
}
