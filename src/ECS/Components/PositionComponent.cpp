#include "PositionComponent.h"

PositionComponent::PositionComponent(float x, float y)
:PositionComponent(sf::Vector2f(x, y))
{}

PositionComponent::PositionComponent(sf::Vector2f position)
:position(position)
{}

PositionComponent::~PositionComponent()
{}

sf::Vector2f PositionComponent::getPosition()const
{
    return position;
}

ComponentID PositionComponent::getTypeId() const
{
    return ID;
}

void PositionComponent::translate(float dx, float dy)
{
    translate(sf::Vector2(dx, dy));
}

void PositionComponent::translate(sf::Vector2f dp)
{
    position += dp;
}

void PositionComponent::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void PositionComponent::setPosition(sf::Vector2f position)
{
    this->position = position;
}

std::string PositionComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (position) :(" << position.x << ", " << position.y << ")";
    return sstr.str();
}
