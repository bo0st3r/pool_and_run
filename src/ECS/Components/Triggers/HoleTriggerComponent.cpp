#include "HoleTriggerComponent.h"

HoleTriggerComponent::HoleTriggerComponent(std::string targetTag)
:TriggerComponent()
{
    this->targetTag = targetTag;
    targetEntity = EntityManagerSingleton::MAX_ENTITY;
}

HoleTriggerComponent::~HoleTriggerComponent()
{}


ComponentID HoleTriggerComponent::getTriggerId() const
{
    return TRIGGER_ID;
}

std::string HoleTriggerComponent::getTargetTag() const
{
    return targetTag;
}

Entity HoleTriggerComponent::getTargetEntity() const
{
    return targetEntity;
}

void HoleTriggerComponent::setTargetEntity(Entity entity)
{
    this->targetEntity = entity;
}


void HoleTriggerComponent::onTrigger(Entity entity, std::string tag)
{
    if(tag == targetTag && !isTriggered())
    {
        setTriggered(true);
        setTargetEntity(entity);
    }
}
