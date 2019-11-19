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

        virtual std::string str() const;

    protected:

    private:
        static inline const float G = 300.0;
};

#endif // GRAVITYCOMPONENT_H
