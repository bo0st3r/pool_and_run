#include "CueAttackTriggerComponent.h"

CueAttackTriggerComponent::CueAttackTriggerComponent()
:TriggerComponent()
{
        targetEntity = EntityManagerSingleton::MAX_ENTITY;
}

CueAttackTriggerComponent::~CueAttackTriggerComponent()
{
    //dtor
}


ComponentID CueAttackTriggerComponent::getTriggerId() const
{
    return TRIGGER_ID;
}

Entity CueAttackTriggerComponent::getTargetEntity() const
{
    return targetEntity;
}

void CueAttackTriggerComponent::setTargetEntity(Entity entity)
{
    this->targetEntity = entity;
}

void CueAttackTriggerComponent::onTrigger(Entity entity, std::string tag)
{
    if(tag == "Joueur" && !isTriggered())
    {
        setTriggered(true);
        setTargetEntity(entity);
    }
}
