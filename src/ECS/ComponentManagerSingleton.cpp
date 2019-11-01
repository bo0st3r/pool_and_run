#include "ComponentManagerSingleton.h"
#include <iostream>

ComponentManagerSingleton::ComponentManagerSingleton()
{}

ComponentManagerSingleton::~ComponentManagerSingleton()
{
    delete instance;
}

ComponentManagerSingleton* ComponentManagerSingleton::getInstance()
{
    if(instance == 0)
    {
        instance = new ComponentManagerSingleton();
    }

    return instance;
}

//template<typename T>
void ComponentManagerSingleton::addComponentToEntity(Component& component, ComponentID componentId, Entity entity) //ajoute un composant donné à l'entité
{
    switch (componentId)
    {
        case PositionComponent::ID :{
                PositionComponent& casted = dynamic_cast<PositionComponent&>(component);
                entityPositions.insert(std::pair<Entity, PositionComponent&>(entity, casted));
                break;
        }

        case VelocityComponent::ID :{
                VelocityComponent& casted = dynamic_cast<VelocityComponent&>(component);
                entityVelocities.insert(std::pair<Entity, VelocityComponent&>(entity, casted));
                break;
        }

        case GravityComponent::ID :{
                GravityComponent& casted = dynamic_cast<GravityComponent&>(component);
                entityGravities.insert(std::pair<Entity, GravityComponent&>(entity, casted));
                break;
        }
    }
}

void ComponentManagerSingleton::removeComponentFromEntity(ComponentID component, Entity entity)
{
    switch(component)
    {
        case PositionComponent::ID : {entityPositions.erase(entity);}break;
        case VelocityComponent::ID : {entityVelocities.erase(entity);}break;
        case GravityComponent::ID : {entityGravities.erase(entity);}break;
    }
}

void ComponentManagerSingleton::removeAllFromEntity(Entity entity)
{
    removeComponentFromEntity(PositionComponent::ID, entity);
    removeComponentFromEntity(VelocityComponent::ID, entity);
    removeComponentFromEntity(GravityComponent::ID, entity);
}

EntityComponentMap<PositionComponent>& ComponentManagerSingleton::getEntityPositionMap()
{
    return entityPositions;
}

EntityComponentMap<VelocityComponent>& ComponentManagerSingleton::getEntityVelocityMap()
{
    return entityVelocities;
}

EntityComponentMap<GravityComponent>& ComponentManagerSingleton::getEntityGravityMap()
{
    return entityGravities;
}

