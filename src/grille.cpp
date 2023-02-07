#include "grille.hpp"
#include "piece.hpp"
#include <SFML/System.hpp>

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

}