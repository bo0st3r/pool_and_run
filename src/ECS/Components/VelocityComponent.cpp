#include "VelocityComponent.h"

VelocityComponent::VelocityComponent()
{
    //ctor
}

VelocityComponent::~VelocityComponent()
{
    //dtor
}

float VelocityComponent::getVx() const
{
    return vx;
}

float VelocityComponent::getVy() const
{
    return vy;
}

ComponentID VelocityComponent::getTypeId() const
{
    return ID;
}

void VelocityComponent::setVx(float vx)
{
    this->vx = vx;
}

void VelocityComponent::setVy(float vy)
{
    this->vy = vy;
}

void VelocityComponent::addVelocity(float dvx, float dvy)
{
    vx += dvx;
    vy += dvy;
}

void VelocityComponent::setVelocity(float vx, float vy)
{
    setVx(vx);
    setVy(vy);
}


std::string VelocityComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " :(" << vx << ", " << vy << ")";
    return sstr.str();
}

