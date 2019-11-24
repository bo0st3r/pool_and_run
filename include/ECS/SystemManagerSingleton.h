#ifndef SYSTEMMANAGERSINGLETON_H
#define SYSTEMMANAGERSINGLETON_H

#include <vector>

#include "PhysicSystem.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "RespawnSystem.h"
#include "TriggerSystem.h"
#include "ControllerSystem.h"

class SystemManagerSingleton
{
    public:
        static SystemManagerSingleton* getInstance();
        virtual ~SystemManagerSingleton();
        static void releaseInstance();


        void addSystem(System* system);
        void addSystem(RenderSystem* system);
        void updateSystems(float dt);
        void updateRender(float dt, sf::RenderWindow& window, sf::View& view);

    protected:

    private:
        SystemManagerSingleton();
        static inline SystemManagerSingleton* instance = 0;

        std::vector<System*> systems;
        RenderSystem* render = 0;

};

#endif // SYSTEMMANAGERSINGLETON_H
