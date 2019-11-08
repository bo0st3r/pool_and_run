#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <Component.h>

class ColliderComponent : public Component
{
    public:
        ColliderComponent(ColliderTypeEnum colliderType = ColliderTypeEnum::Box, bool crossable = false);
        virtual ~ColliderComponent();

        virtual ComponentID getTypeId() const;
        ColliderTypeEnum getColliderType() const;
        bool isCrossable() const;

        static inline const ComponentID ID = 4;

        virtual std::string str() const;

    protected:

    private:
        ColliderTypeEnum colliderType;
        bool crossable;
};

#endif // COLLIDERCOMPONENT_H
