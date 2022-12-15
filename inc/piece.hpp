#ifndef INC_PIECE_HPP
#define INC_PIECE_HPP

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

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

struct point
{
    int x;
    int y;
};


class Piece
{ 
    private:
        point carres[4];


    public:
        explicit Piece(int grille);//construit une pièce aléatoirement dans la grille spécifié
        void rotate();
        void move();
        void affichage();
}
;
#endif