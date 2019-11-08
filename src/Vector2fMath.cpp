#include "Vector2fMath.h"

Vector2fMath::Vector2fMath()
{
    //ctor
}

Vector2fMath::~Vector2fMath()
{
    //dtor
}

float Vector2fMath::distanceBetween(sf::Vector2f v1, sf::Vector2f v2)
{
    sf::Vector2 distanceVector2 = v2 - v1;

    return std::sqrt(std::pow(distanceVector2.x,2) + std::pow(distanceVector2.y,2));
}
