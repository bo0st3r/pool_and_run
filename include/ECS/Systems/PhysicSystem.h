#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include <System.h>

class PhysicSystem : public System
{
    public:
        PhysicSystem(Positions& p, Velocities& v, Gravities& g, Constraints& c);
        virtual ~PhysicSystem();

        virtual void update(float dt);

        void addGravityToVelocity(Entity entity, float dt); //ajoute la force de gravité sur la vélocité des entités possédant les deux composant
        void addVelocityToPosition(Entity entity, float dt); //ajoute la vélocité à la position des entités possédants les deux composant
        void applyConstraints(Entity entity); //applique les contraintes en annulant la velocité si besoin


    protected:

    private:
        Positions* positions;
        Velocities* velocities;
        Gravities* gravities;
        Constraints* constraints;
};

#endif // PHYSICSYSTEM_H
