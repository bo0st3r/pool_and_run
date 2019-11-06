#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <Component.h>


class VelocityComponent : public Component
{
    public:
        VelocityComponent();
        virtual ~VelocityComponent();

        static inline const ComponentID ID = 1;

        sf::Vector2f getVelocity() const;
        virtual ComponentID getTypeId() const;
        static ComponentID getId(){return ID;};

        void addVelocity(float dvx = 0, float dvy = 0);
        void addVelocity(sf::Vector2f dv);
        void setVelocity(float vx = 0, float vy = 0);
        void setVelocity(sf::Vector2f velocity);

        virtual std::string str() const;


    protected:

    private:
        sf::Vector2f velocity;
};

#endif // VELOCITYCOMPONENT_H
