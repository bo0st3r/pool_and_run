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
