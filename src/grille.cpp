#include "grille.hpp"
#include "piece.hpp"
#include <SFML/System.hpp>


Grille::Grille()
{
    for(int i=0;i<hauteur;i++)
    {
      for(int j=0;j<largeur;j++)
      {
        grille[i][j]=0;
      }
    }
}
int Grille::clearLine()
{
    int nb_supprime=0;
    int score=0;
    int k=hauteur-1;
    for (int i=hauteur-1;i>0;i--)
    {
        int count=0;
        for (int j=0;j<largeur;j++)
        {
            if (grille[i][j]) count++;
            grille[k][j]=grille[i][j];
        }
        if (count<largeur) k--;
        else nb_supprime+=1;
    }
    if (nb_supprime==1) return 40;
    else if (nb_supprime==2) return 100;
    else if (nb_supprime==3) return 300;
    else if (nb_supprime==4) return 1200;
    else return 0;    

}

void Grille::ajoutePiece(Piece piece)
{
    for (int i=0;i<4;i++) 
    {
        grille[piece.tampon[i].y][piece.tampon[i].x]=piece.color;
    }
}