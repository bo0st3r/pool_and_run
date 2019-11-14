#include "RespawnComponent.h"

RespawnComponent::RespawnComponent()
{
    //ctor
}

RespawnComponent::~RespawnComponent()
{
    //dtor
}

ComponentID RespawnComponent::getTypeId() const
{
    return ID;
}

std::string RespawnComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (respawn)";
    return sstr.str();
}
