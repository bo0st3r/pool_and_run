#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include <System.h>

class PhysicSystem : public System
{
    public:
        PhysicSystem(Positions& p, Velocities& v, Gravities& g);
        virtual ~PhysicSystem();

        virtual void update(float dt);

        void addGravityToVelocity(Entity entity, float dt); //ajoute la force de gravité sur la vélocité des entités possédant les deux composant
        void addVelocityToPosition(Entity entity, float dt); //ajoute la vélocité à la position des entités possédants les deux composant

    protected:

    private:
        Positions* positions;
        Velocities* velocities;
        Gravities* gravities;
};

#endif // PHYSICSYSTEM_H
