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
                        Constraints& con,
                        sf::Vector2u viewSize
                        );
        virtual ~CollisionSystem();

        virtual void update(float dt);
        void addCollisionConstraints(sf::Sprite s1, sf::Sprite s2, Entity entity);
        bool addViewBorderConstraints(sf::Sprite s, Entity entity);
        void removeCollisionConstraints(Entity entity);
        void transfertVelocity(Entity e1, Entity e2, float absorption);

    protected:

    private:
        Characters* characters;
        Renderers* renderers;
        Positions* positions;
        Velocities* velocities;
        Colliders* colliders;
        Triggers* triggers;
        Constraints* constraints;
        sf::Vector2u viewSize;

        static inline float maxCollidingDistance = 100;
};

#endif // COLLISIONSYSTEM_H
