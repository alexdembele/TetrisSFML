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

// commande avec borne => def protocole
sf::Packet& operator <<(sf::Packet& packet, const Game& game)
{
    std::int16_t buffer;
    std::int16_t score;
    std::int16_t level;
     for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        buffer=game.grille.grille[i][j];
        packet <<  buffer;
        
      }
     
    }
    score=game.score;
    level=game.level;
    packet<<score;
    packet<<level;
    return packet ;
}

sf::Packet& operator >>(sf::Packet& packet, Game& game)
{
  std::int16_t buffer;
  std::int16_t score;
  std::int16_t level;
    for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {

        packet >> buffer;
        game.grille.grille[i][j]=buffer;
        
        
      }
     
    }
    packet<<score;
    packet<<level;
    game.score=score;
    game.level=level;
    
    
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
    sf::Socket::Status status = socket.connect("147.250.224.164",52000);
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

              //prise des commandes claviers
              myGame.commande(e);
        }

    
    socket.setBlocking(false);
   
    
   
    
    
    
    //Actualisation grille
    if (not(myGame.end)&&!myGame.afficheMenu)
    {
      if (myGame.updateGame(temps) )
      {
       temps=0;
       
       
      }
    }
    //echange reseau
    if(tempsReseau>1)
    {
    tempsReseau=0;
    packet.clear();
    packet << myGame;
    
    socket.send(packet);
    
    packet.clear();
    socket.receive(packet);
    
    packet>>gameReseau;
    packet.clear();
    }
    //verification de l'état du jeu
    myGame.levelup();
    myGame.endGame();
    
   
    window.draw(myGame);
    window.draw(gameReseau);
    
    window.display();
    }

    return 0;
}
