#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <Component.h>


class PositionComponent : public Component
{
    public:
        PositionComponent(float x = 0, float y = 0);
        virtual ~PositionComponent();

        float getX() const;
        float getY() const;
        virtual ComponentID getTypeId() const;
        static ComponentID getId(){return id;};
        void setX(float X);
        void setY(float Y);

        void translate(float dx, float dy);
        void setPosition(float x, float y);

        virtual std::string str() const;

    protected:

    private:
        float x;
        float y;
        static inline ComponentID id = 0;
};

#endif // POSITONCOMPONENT_H
