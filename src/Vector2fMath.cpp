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

float Vector2fMath::magnitude(sf::Vector2f v)
{
    return distanceBetween(v, sf::Vector2f(0, 0));
}

float Vector2fMath::angleBetween(sf::Vector2f v1, sf::Vector2f v2)
{
    return std::atan2(v2.x - v1.x, v2.y- v1.y);
}
