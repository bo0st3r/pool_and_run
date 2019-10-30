#ifndef POSITONCOMPONENT_H
#define POSITONCOMPONENT_H

#include <Component.h>


class PositonComponent : public Component
{
    public:
        PositonComponent(float x = 0, float y = 0);
        virtual ~PositonComponent();

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
