#include "PositonComponent.h"

PositonComponent::PositonComponent(float x, float y)
:x(x), y(y)
{}

PositonComponent::~PositonComponent()
{}

float PositonComponent::getX() const
{
    return x;
}

float PositonComponent::getY() const
{
    return y;
}

ComponentID PositonComponent::getTypeId() const
{
    return id;
}

void PositonComponent::setX(float x)
{
    this->x = x;
}

void PositonComponent::setY(float y)
{
    this->y = y;
}

void PositonComponent::translate(float dx, float dy)
{
    x += dx;
    y += dy;
}

void PositonComponent::setPosition(float x, float y)
{
    setX(x);
    setY(y);
}

std::string PositonComponent::str() const
{
    std::stringstream sstr;
    sstr << id << " :(" << x << ", " << y << ")";
    return sstr.str();
}
