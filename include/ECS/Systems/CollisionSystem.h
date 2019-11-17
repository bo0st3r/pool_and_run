#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#define M_PI  3.14159265358979323846

#include <System.h>
#include <Collision.h>
#include "Configuration/Configuration.h"

class CollisionSystem : public System
{
    public:
        CollisionSystem(Characters& cha,
                        Renderers& r,
                        Positions& p,
                        Velocities& ve,
                        Gravities& g,
                        Colliders& col,
                        Triggers& t,
                        Constraints& con,
                        sf::View& v
                        );
        virtual ~CollisionSystem();

        virtual void update(float dt);
        void addCollisionConstraints(sf::Sprite s1, sf::Sprite s2, Entity entity);
        void viewClamping();
        bool addViewBorderConstraints(sf::Sprite s, Entity entity);
        void removeCollisionConstraints(Entity entity);
        void transfertVelocity(Entity e1, Entity e2, float absorption);
        void floorBouncing(Entity character, Entity platform, float absorption);

    protected:

    private:
        Characters* characters;
        Renderers* renderers;
        Positions* positions;
        Velocities* velocities;
        Gravities* gravities;
        Colliders* colliders;
        Triggers* triggers;
        Constraints* constraints;
        sf::View* view;

        static inline float maxCollidingDistance = 45;
        static inline float minBouncingSpeed = 20;
};

#endif // COLLISIONSYSTEM_H
