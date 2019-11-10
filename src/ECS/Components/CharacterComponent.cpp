#include "CharacterComponent.h"

CharacterComponent::CharacterComponent(std::string myName, std::string tag, int live, float speed)
:myName(myName), tag(tag), live(live), speed(speed)
{}

CharacterComponent::~CharacterComponent()
{
    //dtor
}

ComponentID CharacterComponent::getTypeId() const
{
    return ID;
}

std::string CharacterComponent::getMyName() const
{
    return myName;
}

std::string CharacterComponent::getTag() const
{
    return tag;
}

int CharacterComponent::getLive()const
{
    return live;
}

float CharacterComponent::getSpeed()const
{
    return speed;
}

void CharacterComponent::addLive(int amount)
{
    live += amount;
}

std::string CharacterComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (character) : " << myName << ", tag : " << tag;
    return sstr.str();
}
