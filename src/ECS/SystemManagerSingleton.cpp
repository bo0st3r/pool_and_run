#include "SystemManagerSingleton.h"
#include <iostream>

SystemManagerSingleton::SystemManagerSingleton(){
    std::cout << "system" << std::endl;
}

SystemManagerSingleton::~SystemManagerSingleton()
{
    for(System* system : systems)
    {
      delete system;
    }

    delete render;
}


void SystemManagerSingleton::releaseInstance(){
    delete instance;
    instance = 0;
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

void SystemManagerSingleton::updateRender(float dt, sf::RenderWindow& window, sf::View& view)
{
    render->updateRender(dt, window, view);
}


