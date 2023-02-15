#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
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

// regarde si la pièce peut se déplacer
bool check()
{
   for (int i=0;i<4;i++)
      if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
};


int main()
{
    srand(time(0));     
    //chargement graphisme
    RenderWindow window(VideoMode(1800, 1000), "The Game!");

    Texture t1,t2,t3;
    if(!t1.loadFromFile("../Projet/images/tiles.png"))
      printf("Erreur chargement\n");
    if(!t2.loadFromFile("../Projet/images/background.png"))
      printf("Erreur chargement\n");
    if(!t3.loadFromFile("../Projet/images/frame.png"))
      printf("Erreur chargement\n");
    
    Sprite s(t1), background(t2), frame(t3),fram(t3);
    fram.move(Vector2f(450.f,0));
    scaleToMinSize(background,1900,1100);

    //definition des parametres de jeu
    int dx=0; bool rotate=0; int colorNum=1;
    float timer=0,delay=0.3; 


    Clock clock;

    //TEST
    //definition de la grille
    Grille Ter;
    Grille Tertest;
    
    //definition de la piece
    Piece piec;
    Piece piecTest;

    //definition de la partie
    Game myGame(Tertest,piecTest);
    //definition temps
    float temps=0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        temps+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
              if (e.key.code==Keyboard::Up) rotate=true;
              else if (e.key.code==Keyboard::Left) dx=-1;
              else if (e.key.code==Keyboard::Right) dx=1;
              myGame.commande(e);
        }

    if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;
    
    //// <- Move -> ///
    /*for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=dx; } //b est un tampon pour voir si le mouvement de a est valide
    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];*/

    piec.move(dx,Ter);


    //////Rotate//////
    if (rotate)
      {
        /*Point p = a[1]; //center of rotation
        for (int i=0;i<4;i++)
          {
            int x = a[i].y-p.y;
            int y = a[i].x-p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
           }
           if (!check()) for (int i=0;i<4;i++) a[i]=b[i];// b est un tampon pour voir la rotation est valide*/
           piec.rotate(Ter);
      }

    ///////Tick//////
    if (timer>delay)
      {
        /*for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }
        

        if (!check()) // si on ne peut plus bouger, on actualise le terrain et on créé une nouvelle pièce
        {
         for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;

         colorNum=1+rand()%7;
         int n=rand()%7;
         for (int i=0;i<4;i++)
           {
            a[i].x = figures[n][i] % 2 +4; //spawn au centre // A décaler pour le multijoueur
            a[i].y = figures[n][i] / 2;
           }
        }*/
        piec.descend();
        if (!piec.occupe(Ter))
        {
          Ter.ajoutePiece(piec);
          piec.reset();
        }

         timer=0;
      }
    if (myGame.updateGame(temps))
    {
      temps=0;
    }
    printf("%f\n",temps);
    ///////check lines//////////
    /*int k=M-1;
    for (int i=M-1;i>0;i--)
    {
        int count=0;
        for (int j=0;j<N;j++)
        {
            if (field[i][j]) count++;
            field[k][j]=field[i][j];
        }
        if (count<N) k--;
    }*/
    Ter.clearLine();

    dx=0; rotate=0; delay=0.3;

    /////////draw//////////
    window.clear(Color::Black);    
    window.draw(background);
          
    // affichage grille
    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
       {
         if (myGame.grille.grille[i][j]==0) continue;
         s.setTextureRect(IntRect(myGame.grille.grille[i][j]*18,0,18,18));
         s.setPosition(j*18,i*18);
         s.move(28,31); //offset
         window.draw(s);
       }
    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
       {
         if (Ter.grille[i][j]==0) continue;
         s.setTextureRect(IntRect(Ter.grille[i][j]*18,0,18,18));
         s.setPosition(j*18,i*18);
         s.move(478,31); //offset
         window.draw(s);
       }
    //affichage pièce en déplacement
    for (int i=0;i<4;i++)
      {
        s.setTextureRect(IntRect(myGame.piece.color*18,0,18,18));
        s.setPosition(myGame.piece.courant[i].x*18,myGame.piece.courant[i].y*18);
        s.move(28,31); //offset
        window.draw(s);
      }

    for (int i=0;i<4;i++)
      {
        s.setTextureRect(IntRect(piec.color*18,0,18,18));
        s.setPosition(piec.courant[i].x*18,piec.courant[i].y*18);
        s.move(478,31); //offset
        window.draw(s);
      }

    window.draw(frame);
    window.draw(fram);
    window.display();
    }

    return 0;
}
