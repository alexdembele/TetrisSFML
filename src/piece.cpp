#include "piece.hpp"
#include <SFML/System.hpp>

explicit Piece::Piece(int grille)
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


void Piece::rotate(int sens)
{

}

void Piece::move(int direction)
{

}