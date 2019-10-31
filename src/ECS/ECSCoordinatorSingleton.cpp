#include "ECSCoordinatorSingleton.h"

ECSCoordinatorSingleton::ECSCoordinatorSingleton()
{
    //ctor
}

ECSCoordinatorSingleton::~ECSCoordinatorSingleton()
{
    //dtor
}

ECSCoordinatorSingleton* ECSCoordinatorSingleton::getInstance()
{
    if(instance == 0)
    {
        instance = new ECSCoordinatorSingleton();
    }

    return instance;
}

Entity ECSCoordinatorSingleton::createNewEntity()
{
    return entityManager->createNewEntity();
}

void ECSCoordinatorSingleton::removeEntity(Entity entity)
{
    componentManager->removeAllFromEntity(entity);
    entityManager->deleteEntity(entity);
}

template <typename T>
void ECSCoordinatorSingleton::addComponent(ComponentID component)
{
    componentManager->addComponent<T>(component);
}

void ECSCoordinatorSingleton::addComponenntToEntity(Component& component, Entity entity)
{
    componentManager->addComponentToEntity(component, entity);
}

void ECSCoordinatorSingleton::removeComponentFromEntity(ComponentID component, Entity entity)
{
    componentManager->removeComponentFromEntity(component, entity);
}

void ECSCoordinatorSingleton::addSystem(System& system)
{
    systemManager->addSystem(&system);
}

void ECSCoordinatorSingleton::updateSystems(float dt)
{
    systemManager->updateSystems(dt);
}

EntityComponentMap<Component>* ECSCoordinatorSingleton::getEntityComponentMap(ComponentID component)
{
    return componentManager->getEntityComponentMap(component);
}
