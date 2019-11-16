#ifndef ENTITYCREATOR_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ECSCoordinatorSingleton.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "ComponentManagerSingleton.h"

class EntityCreator
{
    public:
        EntityCreator();
        virtual ~EntityCreator();
        static Entity createPlayer(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs);
        static Entity createEnnemyBall(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs);
        static Entity createEnnemyCue(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs);
        static Entity createCheckPoint(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs);
        static void createWarp(float x1, float y1,float x2, float y2, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs);
        static Entity createHole(float x, float y, std::string targetTag, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton ecs);
        static Entity createEndLevel(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton ecs);
        static Entity createTile(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs);



    protected:

    private:
};

#endif // ENTITYCREATOR_H
