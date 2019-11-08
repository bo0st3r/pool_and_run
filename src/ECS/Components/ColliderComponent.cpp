#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(ColliderTypeEnum colliderType, bool crossable)
:colliderType(colliderType), crossable(crossable)
{}

ColliderComponent::~ColliderComponent()
{}

ComponentID ColliderComponent::getTypeId() const
{
    return ID;
}

ColliderTypeEnum ColliderComponent::getColliderType() const
{
    return colliderType;
}

bool ColliderComponent::isCrossable() const
{
    return crossable;
}

std::string ColliderComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (collider) : " << colliderType;
    return sstr.str();
}
