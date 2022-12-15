#ifndef INC_GRILLE_HPP
#define INC_GRILLE_HPP

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

const int hauteur=20;
const int largeur=10;


class Grille
{
    private:
        int grille[hauteur][largeur] ;
    public:
        void clearLine();
        void affichage();
        
};

#endif