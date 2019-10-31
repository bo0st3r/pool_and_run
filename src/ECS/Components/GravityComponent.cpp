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
    return id;
}

std::string GravityComponent::str() const
{
    std::stringstream sstr;
    sstr << id << " : gravity strength = " << G;
    return sstr.str();
}


