#include "PositionComponent.h"

PositionComponent::PositionComponent(float x, float y)
:x(x), y(y)
{}

PositionComponent::~PositionComponent()
{}

float PositionComponent::getX() const
{
    return x;
}

float PositionComponent::getY() const
{
    return y;
}

ComponentID PositionComponent::getTypeId() const
{
    return ID;
}

void PositionComponent::setX(float x)
{
    this->x = x;
}

void PositionComponent::setY(float y)
{
    this->y = y;
}

void PositionComponent::translate(float dx, float dy)
{
    x += dx;
    y += dy;
}

void PositionComponent::setPosition(float x, float y)
{
    setX(x);
    setY(y);
}

std::string PositionComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " :(" << x << ", " << y << ")";
    return sstr.str();
}
