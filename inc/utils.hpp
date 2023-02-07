#ifndef INC_UTILS_H
#define INC_UTILS_H

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "piece.hpp"
#include "grille.hpp"




void setOriginToCenter(sf::Sprite &object);
void setOriginToCenter(sf::Shape &object);
void setOriginToCenter(sf::Text &object);

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y);
void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y);
void scaleByRadius(sf::Sprite &sp, int radius);

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center);



#endif