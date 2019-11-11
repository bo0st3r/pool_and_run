#include "EndLevelTriggerComponent.h"
#include <iostream>

EndLevelTriggerComponent::EndLevelTriggerComponent()
:TriggerComponent()
{}

EndLevelTriggerComponent::~EndLevelTriggerComponent()
{
    //dtor
}

ComponentID EndLevelTriggerComponent::getTriggerId() const
{
    return TRIGGER_ID;
}

void EndLevelTriggerComponent::onTrigger(Entity entity, std::string tag)
{
    if(tag == "Joueur" && !isTriggered())
    {
        setTriggered(true);
    }
}
