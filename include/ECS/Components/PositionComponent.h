

#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <Component.h>


class PositionComponent : public Component
{
    public:
        PositionComponent(float x = 0, float y = 0); //crée une position sur base de 2 réels
        PositionComponent(sf::Vector2f position); // crée une position sur base d'un vecteur2 de réels
        virtual ~PositionComponent();

        static inline const ComponentID ID = 0; //l'ID du composant

        sf::Vector2f getPosition() const;
        virtual ComponentID getTypeId() const;

        void translate(float dx, float dy); //déplace la position selon 2 réels
        void translate(sf::Vector2f dp); //déplace la position selon un vecteur2 de réels
        void setPosition(float x, float y); //change la position selon 2 réels
        void setPosition(sf::Vector2f position); //change la position selon un vecteur2 de réels;

        virtual std::string str() const;

    protected:

    private:
        sf::Vector2f position;
};

#endif // POSITONCOMPONENT_H
