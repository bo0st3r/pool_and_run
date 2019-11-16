#include "SystemManagerSingleton.h"
#include <iostream>

SystemManagerSingleton::SystemManagerSingleton()
{}

SystemManagerSingleton::~SystemManagerSingleton()
{

    for(System* system : systems)
    {
      delete system;
    }

    delete instance;
    delete render;
}

SystemManagerSingleton* SystemManagerSingleton::getInstance()
{
    if(instance == 0)
    {
        instance = new SystemManagerSingleton();
    }

    return instance;
}

void SystemManagerSingleton::addSystem(System* system)
{
    systems.push_back(system);
}

void SystemManagerSingleton::addSystem(RenderSystem* system)
{
    systems.push_back(system);
    render = system;
}

void SystemManagerSingleton::updateSystems(float dt)
{
    for(System* system : systems)
    {
        if(system != render)
        {
            system->update(dt);
        }
    }
}

void SystemManagerSingleton::updateRender(float dt, sf::RenderWindow& view)
{
    render->updateRender(dt, view);
}


