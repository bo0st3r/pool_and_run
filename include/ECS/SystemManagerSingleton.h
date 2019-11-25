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

        void addSystem(System* system); //ajoute un systeme à l'ECS
        void addSystem(RenderSystem* system); //ajoute le systeme qui gère le rendu à l'ECS
        void updateSystems(float dt); //met a jour tous les système dans leur ordre d'ajout
        void updateRender(float dt, sf::RenderWindow& window, sf::View& view); //permet de mettre a jour le rendu séparement des autres systèmes

    protected:

    private:
        SystemManagerSingleton();
        static inline SystemManagerSingleton* instance = 0;

        std::vector<System*> systems;
        RenderSystem* render = 0; //le systeme de rendu, sera ignoré dans l'updateSystems

};

#endif // SYSTEMMANAGERSINGLETON_H
