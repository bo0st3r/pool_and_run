#include "ECSCoordinatorSingleton.h"
#include <iostream>

ECSCoordinatorSingleton::ECSCoordinatorSingleton()
{
    //ctor
}

ECSCoordinatorSingleton::~ECSCoordinatorSingleton()
{

}

void ECSCoordinatorSingleton::releaseInstance()
{
    SystemManagerSingleton::releaseInstance();
    ComponentManagerSingleton::releaseInstance();
    EntityManagerSingleton::releaseInstance();
    delete instance;
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

void ECSCoordinatorSingleton::addSystem(System* system)
{
    systemManager->addSystem(system);
}

void ECSCoordinatorSingleton::addSystem(RenderSystem* render)
{
    systemManager->addSystem(render);
}

void ECSCoordinatorSingleton::updateSystems(float dt)
{
    systemManager->updateSystems(dt);
}

void ECSCoordinatorSingleton::updateRender(float dt, sf::RenderWindow& window, sf::View& view)
{
    systemManager->updateRender(dt, window, view);
}
