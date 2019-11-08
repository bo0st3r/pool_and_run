#ifndef SYSTEMMANAGERSINGLETON_H
#define SYSTEMMANAGERSINGLETON_H

#include <vector>

#include <PhysicSystem.h>
#include <RenderSystem.h>
#include <CollisionSystem.h>

class SystemManagerSingleton
{
    public:
        static SystemManagerSingleton* getInstance();
        virtual ~SystemManagerSingleton();

        void addSystem(System* system);
        void updateSystems(float dt);

    protected:

    private:
        SystemManagerSingleton();
        static inline SystemManagerSingleton* instance = 0;

        std::vector<System*> systems;

};

#endif // SYSTEMMANAGERSINGLETON_H
