#include "piece.hpp"
#include <SFML/System.hpp>

Piece::Piece(int grille, int** figures)
{
    int typePiece = rand()%7;
         for (int i=0;i<4;i++)
           {
            courant[i].x = figures[typePiece][i] % 2 +4; //spawn au centre // A décaler pour le multijoueur
            courant[i].y = figures[typePiece][i] / 2;
            tampon[i].x=0;
            tampon[i].y=0;
           }
}


void Piece::rotate()
{
  point p =courant[1]; // centre de rotation
  for (int j=0;j<4;j++)
  {
    int x = courant[j].y-p.y;
    int y = courant[j].x-p.x;
    courant[j].x=p.x-x;
    courant[j].y=p.y+y;
  }
  for(int j=0;j<4;j++)
  {
    courant[j]=tampon[j];
  }
}

void Piece::move(int direction)
{

}