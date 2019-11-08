#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <System.h>
#include <Collision.h>

class CollisionSystem : public System
{
    public:
        CollisionSystem(Characters& cha,
                        Renderers& r,
                        Positions& p,
                        Velocities& ve,
                        Colliders& col,
                        Triggers& t,
                        Constraints& con
                        );
        virtual ~CollisionSystem();

        virtual void update(float dt);
        void addCollisionConstraints(sf::Sprite s1, sf::Sprite s2, Entity e1);

    protected:

    private:
        Characters* characters;
        Renderers* renderers;
        Positions* positions;
        Velocities* velocities;
        Colliders* colliders;
        Triggers* triggers;
        Constraints* constraints;

        static inline float maxCollidingDistance = 50;
};

#endif // COLLISIONSYSTEM_H
