#include "piece.hpp"
#include "utils.hpp"
#include "grille.hpp"
#include <SFML/System.hpp>

Piece::Piece(int** figures)
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

bool Piece::occupe(Grille grille)
{
  for (int i=0;i<4;i++)
      if (courant[i].x<0 || courant[i].x>=largeur || courant[i].y>=hauteur) return 0;
      else if (grille.grille[courant[i].y][courant[i].x]) return 0;

   return 1;
}

void Piece::rotate(Grille grille)
{
  point p =courant[1]; // centre de rotation
  for (int j=0;j<4;j++)
  {
    int x = courant[j].y-p.y;
    int y = courant[j].x-p.x;
    courant[j].x=p.x-x;
    courant[j].y=p.y+y;
  }
  if (!occupe( grille))
  {
    for(int j=0;j<4;j++)
    {
      courant[j]=tampon[j];
    }
  }
}

void Piece::move(int direction, Grille grille)
{
  for (int i=0;i<4;i++) 
  { 
    tampon[i]=courant[i]; 
    courant[i].x+=direction; 
  }
  if (!occupe(grille)) 
  {
    for (int i=0;i<4;i++) 
    {
      courant[i]=tampon[i];
    }
  }

}