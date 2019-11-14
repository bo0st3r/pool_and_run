#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(ColliderTypeEnum colliderType, bool crossable, float impactAbsorption)
:colliderType(colliderType), crossable(crossable), impactAbsorption(impactAbsorption)
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

float ColliderComponent::getImpactAbsorption()const
{
    return impactAbsorption;
}

std::string ColliderComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (collider) : " << colliderType;
    return sstr.str();
}
