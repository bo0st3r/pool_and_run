#ifndef VECTOR2FMATH_H
#define VECTOR2FMATH_H

#include <cmath>

#include <SFML/System.hpp>

class Vector2fMath
{
    public:
        Vector2fMath();
        virtual ~Vector2fMath();

        static float distanceBetween(sf::Vector2f v1, sf::Vector2f v2);
        static float magnitude(sf::Vector2f v);
        static float angleBetween(sf::Vector2f v1, sf::Vector2f v2);

    protected:

    private:
};

#endif // VECTOR2FMATH_H
