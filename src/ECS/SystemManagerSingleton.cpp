#include "SystemManagerSingleton.h"

SystemManagerSingleton::SystemManagerSingleton()
{}

SystemManagerSingleton::~SystemManagerSingleton()
{

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
//    for(System* system : systems)
//    {
//        delete system;
//    }

    delete instance;
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

void SystemManagerSingleton::updateSystems(float dt)
{
    for(System* system : systems)
    {
        system->update(dt);
    }
}


