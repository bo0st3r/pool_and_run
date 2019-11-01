#include "GravityComponent.h"

GravityComponent::GravityComponent()
{
    //ctor
}

GravityComponent::~GravityComponent()
{
    //dtor
}

ComponentID GravityComponent::getTypeId() const
{
    return ID;
}

std::string GravityComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " : gravity strength = " << G;
    return sstr.str();
}


