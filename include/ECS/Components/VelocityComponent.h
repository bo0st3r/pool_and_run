

#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <Component.h>


class VelocityComponent : public Component
{
    public:
        VelocityComponent();
        virtual ~VelocityComponent();

        static inline const ComponentID ID = 1; //l'ID du composant

        sf::Vector2f getVelocity() const;
        virtual ComponentID getTypeId() const;

        void addVelocity(float dvx = 0, float dvy = 0); //ajoute une vitesse selon 2 réels
        void addVelocity(sf::Vector2f dv); //ajoute une vitesse  selon un vecteur2 de réels
        void setVelocity(float vx = 0, float vy = 0); //fixe la vitesse selon 2 réels
        void setVelocity(sf::Vector2f velocity); //fixe la vitesse selon un vecteur2 de réels

        virtual std::string str() const;


    protected:

    private:
        sf::Vector2f velocity; //vitesse en pixels/seconde
};

#endif // VELOCITYCOMPONENT_H
