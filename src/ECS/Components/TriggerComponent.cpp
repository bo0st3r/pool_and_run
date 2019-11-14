#include "TriggerComponent.h"

TriggerComponent::TriggerComponent()
{
    triggered = false;
}

TriggerComponent::~TriggerComponent()
{
    //dtor
}

ComponentID TriggerComponent::getTypeId() const
{
    return ID;
}

bool TriggerComponent::isTriggered()const
{
    return triggered;
}

void TriggerComponent::setTriggered(bool triggered)
{
    this->triggered = triggered;
}

std::string TriggerComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (trigger)";
    return sstr.str();
}
