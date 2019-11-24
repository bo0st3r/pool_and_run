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
                        sf::View& v,
                        std::unordered_map<int, Entity>& temp
                        );
        virtual ~CollisionSystem();

        virtual void update(float dt);
        void addCollisionConstraints(sf::Sprite s1, sf::Sprite s2, Entity entity);
        void viewClamping();
        bool addViewBorderConstraints(sf::Sprite s, Entity entity);
        void removeCollisionConstraints(Entity entity);
        void transfertVelocity(Entity e1, Entity e2, float absorption);
        void floorBouncing(Entity character, Entity platform, float absorption);

        bool tryCollision(Entity e1, PositionComponent& p1, ColliderComponent& co1, RendererComponent& r1, CharacterComponent& ch1,
                          Entity e2, PositionComponent& p2, ColliderComponent& co2, RendererComponent& r2);

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

        std::unordered_map<int, Entity>* tileEntityMap;

        static inline float maxCollidingDistance = 50;
        static inline float minBouncingSpeed = 5;
};

#endif // COLLISIONSYSTEM_H
