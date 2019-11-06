#include "RendererComponent.h"

RendererComponent::RendererComponent(std::string textureName)
:textureName(textureName)
{}

RendererComponent::~RendererComponent()
{}

ComponentID RendererComponent::getTypeId() const
{
    return ID;
}

std::string RendererComponent::getTextureName() const
{
    return textureName;
}

sf::Sprite& RendererComponent::getSpriteRef()
{
    return sprite;
}

bool RendererComponent::hasSpriteTextured() const
{
    return sprite.getTexture() != nullptr;
}

std::string RendererComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " : " << textureName;
    return sstr.str();
}
