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
void Grille::clearLine()
{
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
    }

}

void Grille::ajoutePiece(Piece piece)
{
    for (int i=0;i<4;i++) 
    {
        grille[piece.tampon[i].y][piece.tampon[i].x]=piece.color;
    }
}