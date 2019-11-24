#include "EntityCreator.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ECSCoordinatorSingleton.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "ComponentManagerSingleton.h"

#include <iostream>


EntityCreator::EntityCreator()
{
    //ctor
}

EntityCreator::~EntityCreator()
{
    //dtor
}

//methode pour la creation d'un joueur
Entity EntityCreator::createPlayer(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity player = ecs.createNewEntity();

    compManager.addComponentToEntity(*(new CharacterComponent("Héro", TAG_PLAYER, 8)), CharacterComponent::ID, player);
    compManager.addComponentToEntity(*(new RendererComponent(textureName, sf::Vector2f(0.075, 0.075), 4)), RendererComponent::ID, player);
    compManager.addComponentToEntity(*(new PositionComponent(x, y)), PositionComponent::ID, player);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, player);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, player);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, player);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0.8)), ColliderComponent::ID, player);
    compManager.addComponentToEntity(*(new ControllerComponent(100, 100, 200, 5)), ControllerComponent::ID, player);
    return player;
}

Entity EntityCreator::createTile(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){
    Entity platform = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("tile", sf::Vector2f(1, 1), -1)), RendererComponent::ID, platform);
    compManager.addComponentToEntity(*(new PositionComponent(x,y)), PositionComponent::ID, platform);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, false, 0.6)), ColliderComponent::ID, platform);

    return platform;
}
//création d'un ennemi boule
Entity EntityCreator::createEnnemyBall(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity ball = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new CharacterComponent("Boule", TAG_ENEMY_BALL, 0)), CharacterComponent::ID, ball);
    compManager.addComponentToEntity(*(new RendererComponent(textureName, sf::Vector2f(0.07, 0.07), 3)), RendererComponent::ID, ball);
    compManager.addComponentToEntity(*(new PositionComponent(x, y)), PositionComponent::ID, ball);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, ball);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, ball);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, ball);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0.8)), ColliderComponent::ID, ball);

    return ball;
}

//création d'un ennemi queue
Entity EntityCreator::createEnnemyCue(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs) {
    Entity cue = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new CharacterComponent("Queue", TAG_ENEMY_CUE, 0)), CharacterComponent::ID, cue);
    compManager.addComponentToEntity(*(new RendererComponent("ball2", sf::Vector2f(0.1, 0.1), 3)), RendererComponent::ID, cue);
    compManager.addComponentToEntity(*(new PositionComponent(x, y)), PositionComponent::ID, cue);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, cue);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, cue);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, cue);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0)), ColliderComponent::ID, cue);
    compManager.addComponentToEntity(*(new CueAttackTriggerComponent()), TriggerComponent::ID, cue);

    return cue;
}

//création du point de point de controle
Entity EntityCreator::createCheckPoint(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity checkPoint = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball12", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new PositionComponent(x, y)), PositionComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new CheckPointTriggerComponent()), TriggerComponent::ID, checkPoint);

    return checkPoint;
}


//creation de la zone de téléportation
void EntityCreator::createWarp(float x1, float y1,float x2, float y2,  ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity warp1 = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball7", sf::Vector2f(0.1, 0.1),2)), RendererComponent::ID, warp1);
    compManager.addComponentToEntity(*(new PositionComponent(x1, y1)), PositionComponent::ID, warp1);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, warp1);
    compManager.addComponentToEntity(*(new WarpTriggerComponent(sf::Vector2f(x2, y2), true)), TriggerComponent::ID, warp1);

    Entity warp2 = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball7", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, warp2);
    compManager.addComponentToEntity(*(new PositionComponent(x2, y2)), PositionComponent::ID, warp2);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, warp2);
    compManager.addComponentToEntity(*(new WarpTriggerComponent(sf::Vector2f(x1, y1), false)), TriggerComponent::ID, warp2);

}
//creation des trous
Entity EntityCreator::createHole(float x, float y, std::string targetTag, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity hole = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball9", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, hole);
    compManager.addComponentToEntity(*(new PositionComponent(x, y)), PositionComponent::ID, hole);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, hole);
    compManager.addComponentToEntity(*(new HoleTriggerComponent(targetTag)), TriggerComponent::ID, hole);
}

//creation de la fin du niveau
Entity EntityCreator::createEndLevel(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton ecs){

    Entity endLevel = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball8", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new PositionComponent(150, 350)), PositionComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new EndLevelTriggerComponent()), TriggerComponent::ID, endLevel);

}
