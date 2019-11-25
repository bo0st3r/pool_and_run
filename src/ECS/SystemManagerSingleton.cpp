
#include "SystemManagerSingleton.h"

SystemManagerSingleton::SystemManagerSingleton(){}

SystemManagerSingleton::~SystemManagerSingleton()
{
    for(System* system : systems) //supprime chacun des pointeurs de système
    {
      delete system;
    }
    delete render; //supprime le poirteur du renderSystem
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


