#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <Component.h>


class PositionComponent : public Component
{
    public:
        PositionComponent(float x = 0, float y = 0);
        PositionComponent(sf::Vector2f position);
        virtual ~PositionComponent();

        static inline const ComponentID ID = 0;

        sf::Vector2f getPosition() const;
        virtual ComponentID getTypeId() const;
        static ComponentID getId(){return ID;};

        void translate(float dx, float dy);
        void translate(sf::Vector2f dp);
        void setPosition(float x, float y);
        void setPosition(sf::Vector2f position);

        virtual std::string str() const;

    protected:

    private:
        sf::Vector2f position;
};

#endif // POSITONCOMPONENT_H
