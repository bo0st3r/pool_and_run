#include "VelocityComponent.h"

VelocityComponent::VelocityComponent()
{
    //ctor
}

VelocityComponent::~VelocityComponent()
{
    //dtor
}

sf::Vector2f VelocityComponent::getVelocity() const
{
    return velocity;
}

ComponentID VelocityComponent::getTypeId() const
{
    return ID;
}

void VelocityComponent::addVelocity(float dvx, float dvy)
{
    addVelocity(sf::Vector2f(dvx, dvy));
}

void VelocityComponent::addVelocity(sf::Vector2f dv)
{
    velocity += dv;
}

void VelocityComponent::setVelocity(float vx, float vy)
{
    setVelocity(sf::Vector2f(vx, vy));
}

void VelocityComponent::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}


std::string VelocityComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (velocity) :(" << velocity.x << ", " << velocity.y << ")";
    return sstr.str();
}

