#ifndef GRAVITYCOMPONENT_H
#define GRAVITYCOMPONENT_H

#include <Component.h>


class GravityComponent : public Component
{
    public:
        GravityComponent();
        virtual ~GravityComponent();

        static inline const ComponentID ID = 2;

        static float getG(){return G;};
        virtual ComponentID getTypeId() const;
        static ComponentID getId(){return ID;};

        virtual std::string str() const;

    protected:

    private:
        static inline const float G = 9.81;
};

#endif // GRAVITYCOMPONENT_H
