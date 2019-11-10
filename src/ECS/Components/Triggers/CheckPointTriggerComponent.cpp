#include "CheckPointTriggerComponent.h"
#include <iostream>

CheckPointTriggerComponent::CheckPointTriggerComponent()
{
    //ctor
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

bool CheckPointTriggerComponent::isTriggered()const
{
    return triggered;
}

void CheckPointTriggerComponent::setLastTriggered(bool lastTriggered)
{
    this->lastTriggered = lastTriggered;
}

void CheckPointTriggerComponent::setTriggered(bool triggered)
{
    this->triggered = triggered;
}

void CheckPointTriggerComponent::onTrigger(Entity entity, std::string tag)
{
    if(tag == "Joueur" && !lastTriggered && !triggered)
    {
        std::cout << "triggered" << std::endl;
        setTriggered(true);
        //setLastTriggered(true);
    }
}


