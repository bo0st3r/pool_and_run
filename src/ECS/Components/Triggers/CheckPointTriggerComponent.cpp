#include "CheckPointTriggerComponent.h"
#include <iostream>

CheckPointTriggerComponent::CheckPointTriggerComponent()
:TriggerComponent()
{
}

CheckPointTriggerComponent::~CheckPointTriggerComponent()
{
    //dtor
}

ComponentID CheckPointTriggerComponent::getTriggerId() const
{
    return TRIGGER_ID;
}

bool CheckPointTriggerComponent::isLastTriggered()const
{
    return lastTriggered;
}

void CheckPointTriggerComponent::setLastTriggered(bool lastTriggered)
{
    this->lastTriggered = lastTriggered;
}

void CheckPointTriggerComponent::onTrigger(Entity entity, std::string tag)
{
    if(tag == "Joueur" && !lastTriggered && !isTriggered())
    {
        std::cout << "feministe" << std::endl;
        setTriggered(true);
    }
}


