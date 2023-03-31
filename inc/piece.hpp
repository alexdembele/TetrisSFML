#ifndef INC_PIECE_HPP
#define INC_PIECE_HPP

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include "grille.hpp"
#include "utils.hpp"


class Grille;
struct point
{
    int x;
    int y;
};


class Piece
{ 
    public:
        point courant[4];
        point tampon[4];
        int color;


    public:
        Piece();//construit une pièce aléatoirement dans la grille spécifié
        void rotate(Grille grille);
        void move(int direcion, Grille grille);
        bool occupe( Grille grille);
        void reset();
        void descend();
}
;
#endif