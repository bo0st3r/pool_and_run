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

        case RendererComponent::ID :{
                RendererComponent& casted = dynamic_cast<RendererComponent&>(component);
                entityRenderers.insert(std::pair<Entity, RendererComponent&>(entity, casted));
                break;
        }

        case ColliderComponent::ID :{
                ColliderComponent& casted = dynamic_cast<ColliderComponent&>(component);
                entityColliders.insert(std::pair<Entity, ColliderComponent&>(entity, casted));
                break;
        }

        case TriggerComponent::ID :{
                TriggerComponent& casted = dynamic_cast<TriggerComponent&>(component);
                entityTriggers.insert(std::pair<Entity, TriggerComponent&>(entity, casted));
                break;
        }

        case CharacterComponent::ID :{
                CharacterComponent& casted = dynamic_cast<CharacterComponent&>(component);
                entityCharacters.insert(std::pair<Entity, CharacterComponent&>(entity, casted));
                break;
        }

        case ConstraintComponent::ID :{
                ConstraintComponent& casted = dynamic_cast<ConstraintComponent&>(component);
                entityConstraints.insert(std::pair<Entity, ConstraintComponent&>(entity, casted));
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
        case RendererComponent::ID : {entityRenderers.erase(entity);}break;
        case ColliderComponent::ID : {entityColliders.erase(entity);}break;
        case TriggerComponent::ID : {entityTriggers.erase(entity);}break;
        case CharacterComponent::ID : {entityCharacters.erase(entity);}break;
        case ConstraintComponent::ID : {entityConstraints.erase(entity);}break;
    }
}

void ComponentManagerSingleton::removeAllFromEntity(Entity entity)
{
    removeComponentFromEntity(PositionComponent::ID, entity);
    removeComponentFromEntity(VelocityComponent::ID, entity);
    removeComponentFromEntity(GravityComponent::ID, entity);
    removeComponentFromEntity(RendererComponent::ID, entity);
    removeComponentFromEntity(ColliderComponent::ID, entity);
    removeComponentFromEntity(TriggerComponent::ID, entity);
    removeComponentFromEntity(CharacterComponent::ID, entity);
    removeComponentFromEntity(ConstraintComponent::ID, entity);
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

EntityComponentMap<RendererComponent>& ComponentManagerSingleton::getEntityRendererMap()
{
    return entityRenderers;
}

EntityComponentMap<ColliderComponent>& ComponentManagerSingleton::getEntityColliderMap()
{
    return entityColliders;
}

EntityComponentMap<TriggerComponent>& ComponentManagerSingleton::getEntityTriggerMap()
{
    return entityTriggers;
}

EntityComponentMap<CharacterComponent>& ComponentManagerSingleton::getEntityCharacterMap()
{
    return entityCharacters;
}

EntityComponentMap<ConstraintComponent>& ComponentManagerSingleton::getEntityConstraintMap()
{
    return entityConstraints;
}

