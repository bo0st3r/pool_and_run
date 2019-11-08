#include "TriggerComponent.h"

TriggerComponent::TriggerComponent()
{
    //ctor
}

TriggerComponent::~TriggerComponent()
{
    //dtor
}

ComponentID TriggerComponent::getTypeId() const
{
    return ID;
}

std::string TriggerComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (trigger)";
    return sstr.str();
}
