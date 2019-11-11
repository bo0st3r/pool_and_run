#include "WarpTriggerComponent.h"
#include <iostream>

WarpTriggerComponent::WarpTriggerComponent(sf::Vector2f destination, bool exitToRight)
:TriggerComponent()
{
    this->destination = destination;
    this->exitToRight = exitToRight;
    targetEntity = EntityManagerSingleton::MAX_ENTITY;
}

WarpTriggerComponent::~WarpTriggerComponent()
{}

ComponentID WarpTriggerComponent::getTriggerId() const
{
    return TRIGGER_ID;
}

sf::Vector2f WarpTriggerComponent::getDestination() const
{
    return destination;
}

bool WarpTriggerComponent::isExitToRight() const
{
    return exitToRight;
}

Entity WarpTriggerComponent::getTargetEntity() const
{
    return targetEntity;
}

void WarpTriggerComponent::setTargetEntity(Entity entity)
{
    this->targetEntity = entity;
}


void WarpTriggerComponent::onTrigger(Entity entity, std::string tag)
{
    if(tag == "Joueur" && !isTriggered())
    {
        setTriggered(true);
        setTargetEntity(entity);
        //si oui le systeme va téléporter le joueur derriere la sortie
    }
}
