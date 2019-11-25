#ifndef GRAVITYCOMPONENT_H
#define GRAVITYCOMPONENT_H

#include <Component.h>


class GravityComponent : public Component
{
    public:
        GravityComponent();
        virtual ~GravityComponent();

        static inline const ComponentID ID = 2; //l'ID du composant

        static float getG(){return G;};
        virtual ComponentID getTypeId() const;

        virtual std::string str() const;

    protected:

    private:
        static inline const float G = 300.0; //force de gravité en pixel/seconde^2
};

#endif // GRAVITYCOMPONENT_H
