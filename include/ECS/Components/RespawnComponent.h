#ifndef RESPAWNCOMPONENT_H
#define RESPAWNCOMPONENT_H

#include <Component.h>


class RespawnComponent : public Component
{
    public:
        RespawnComponent();
        virtual ~RespawnComponent();
        virtual ComponentID getTypeId() const;

        virtual std::string str() const;

        static inline const ComponentID ID = 8;


    protected:

    private:
};

#endif // RESPAWNCOMPONENT_H
