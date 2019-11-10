#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <Component.h>

class ColliderComponent : public Component
{
    public:
        ColliderComponent(ColliderTypeEnum colliderType = ColliderTypeEnum::Box, bool crossable = false, float impactAbsorption = 0);
        virtual ~ColliderComponent();

        virtual ComponentID getTypeId() const;
        ColliderTypeEnum getColliderType() const;

        bool isCrossable() const;
        float getImpactAbsorption() const;

        static inline const ComponentID ID = 4;

        virtual std::string str() const;

    protected:

    private:
        ColliderTypeEnum colliderType;
        float impactAbsorption; //proportion de vélocité reçue en cas d'impact
        bool crossable; //possibilité de passer au travers du collider
};

#endif // COLLIDERCOMPONENT_H
