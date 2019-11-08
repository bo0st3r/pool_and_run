#include "CharacterComponent.h"

CharacterComponent::CharacterComponent(std::string myName, std::string tag)
:myName(myName), tag(tag)
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

std::string CharacterComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (character) : " << myName << ", tag : " << tag;
    return sstr.str();
}
