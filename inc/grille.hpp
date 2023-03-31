#ifndef INC_GRILLE_HPP
#define INC_GRILLE_HPP

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include "piece.hpp"

const int hauteur=20;
const int largeur=10;

class Piece;
class Grille
{
    public:
        int grille[hauteur][largeur] ;
    public:
        Grille();
        int clearLine();
        void ajoutePiece(Piece piece);
        
        void eclairTombe();
        void asteroideTombe();
        void suppLigne();
        void suppColonne();
        
};

#endif