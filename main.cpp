#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"

#include "ECSCoordinatorSingleton.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "EntityCreator.h"

using std::cout;
using std::endl;


bool test(){
    return true;
}
int main()
{
    pr::AssetManager am;
    am.loadTexture("ball", pr::AssetManager::BALLS_PATH + "ball0.png");

    sf::Sprite ballSprite;
    am.setSpriteTexture(ballSprite, "ball");
    ballSprite.scale(sf::Vector2f(0.1, 0.1));

    pr::InputManager im;

    sf::RenderWindow window(sf::VideoMode(600, 1000), "SFML works!");
    /*while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    switch(event.mouseButton.button){
                        case sf::Mouse::Left:{
                            if(im.isSpriteClicked(ballSprite, sf::Mouse::Left, window)){
                                cout << "clicked" << endl;
                            }

                            break;
                        }
                    }
            }
        }

        window.clear();
        if(ballSprite.getTexture() != nullptr){
            window.draw(ballSprite);
        }
        window.display();
    }*/

    // Getting instances of ECS Coordinator and ComponenManager singletons
    ECSCoordinatorSingleton& ecs = *(ECSCoordinatorSingleton::getInstance());
    ComponentManagerSingleton& compManager = *(ComponentManagerSingleton::getInstance());

    //ajout des systemes
    PhysicSystem physicSystem = PhysicSystem(
                                        compManager.getEntityPositionMap(),
                                        compManager.getEntityVelocityMap(),
                                        compManager.getEntityGravityMap(),
                                        compManager.getEntityConstraintMap()
                                       );

    RenderSystem renderSystem = RenderSystem(
                                       compManager.getEntityPositionMap(),
                                       compManager.getEntityRendererMap(),
                                       window,
                                       am
                                       );

    CollisionSystem collisionSystem = CollisionSystem(
                                        compManager.getEntityCharacterMap(),
                                        compManager.getEntityRendererMap(),
                                        compManager.getEntityPositionMap(),
                                        compManager.getEntityVelocityMap(),
                                        compManager.getEntityColliderMap(),
                                        compManager.getEntityTriggerMap(),
                                        compManager.getEntityConstraintMap(),
                                        window.getView()
                                        );

    RespawnSystem respawnSystem = RespawnSystem(
                                                 compManager.getEntityRespawnMap(),
                                                 compManager.getEntityCharacterMap(),
                                                 compManager.getEntityPositionMap(),
                                                 compManager.getEntityVelocityMap(),
                                                 compManager.getEntityTriggerMap()
                                                 );

    TriggerSystem triggerSystem = TriggerSystem(
                                                compManager.getEntityTriggerMap(),
                                                compManager.getEntityPositionMap(),
                                                compManager.getEntityVelocityMap(),
                                                compManager.getEntityRendererMap()
                                                );
    ecs.addSystem(collisionSystem);
    ecs.addSystem(triggerSystem);
    ecs.addSystem(physicSystem);
    ecs.addSystem(renderSystem);
    ecs.addSystem(respawnSystem);

    //représentation du joueur
<<<<<<< HEAD
    Entity player = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new CharacterComponent("Héro", "Joueur", 8, 10.0)), CharacterComponent::ID, player);
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 4)), RendererComponent::ID, player);
    compManager.addComponentToEntity(*(new PositionComponent(200, 0)), PositionComponent::ID, player);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, player);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, player);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, player);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0.8)), ColliderComponent::ID, player);

    //représentation des plateforme
    Entity platform = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), -1)), RendererComponent::ID, platform);
    compManager.addComponentToEntity(*(new PositionComponent(200,300)), PositionComponent::ID, platform);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, false, 0.5)), ColliderComponent::ID, platform);

    Entity enemyPlatform = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), -1)), RendererComponent::ID, enemyPlatform);
    compManager.addComponentToEntity(*(new PositionComponent(300,500)), PositionComponent::ID, enemyPlatform);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, false, 0.5)), ColliderComponent::ID, enemyPlatform);
=======
    EntityCreator::createPlayer(200,0, "ball",compManager, ecs);
    EntityCreator::createPlayer(300,50, "ball",compManager, ecs);


>>>>>>> f036d28b0899a9b01aac85a75fcd24809cc89245

    //représentation des plateforme
    EntityCreator::createTile(200,300, "ball",compManager, ecs);
    EntityCreator::createTile(300,500, "ball",compManager, ecs);

    //représentation d'un ennemis (boule)
<<<<<<< HEAD

    Entity ball = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new CharacterComponent("Boule", "Ennemi", 0, 10.0)), CharacterComponent::ID, ball);
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 3)), RendererComponent::ID, ball);
    compManager.addComponentToEntity(*(new PositionComponent(210, 250)), PositionComponent::ID, ball);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, ball);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, ball);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, ball);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0.8)), ColliderComponent::ID, ball);

    //représentation d'un ennemis (queue) + test trigger attaque
    Entity cue = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new CharacterComponent("Queue", "Ennemi", 0, 10.0)), CharacterComponent::ID, cue);
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 3)), RendererComponent::ID, cue);
    compManager.addComponentToEntity(*(new PositionComponent(330, 450)), PositionComponent::ID, cue);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, cue);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, cue);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, cue);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0)), ColliderComponent::ID, cue);
    compManager.addComponentToEntity(*(new CueAttackTriggerComponent()), TriggerComponent::ID, cue);

    //test trigger checkPoint
    Entity start = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, start);
    compManager.addComponentToEntity(*(new PositionComponent(200, 50)), PositionComponent::ID, start);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, start);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, start);
    compManager.addComponentToEntity(*(new CheckPointTriggerComponent()), TriggerComponent::ID, start);

    Entity checkPoint = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new PositionComponent(300, 400)), PositionComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new CheckPointTriggerComponent()), TriggerComponent::ID, checkPoint);

    //test trigger warp
    Entity warp = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, warp);
    compManager.addComponentToEntity(*(new PositionComponent(100, 350)), PositionComponent::ID, warp);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, warp);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, warp);
    compManager.addComponentToEntity(*(new WarpTriggerComponent(sf::Vector2f(300, 0), true)), TriggerComponent::ID, warp);

    //test trigger hole
    Entity hole = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, hole);
    compManager.addComponentToEntity(*(new PositionComponent(300, 350)), PositionComponent::ID, hole);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, hole);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, hole);
    compManager.addComponentToEntity(*(new HoleTriggerComponent("Ennemi")), TriggerComponent::ID, hole);

    //test trigger fin de niveau
    Entity endLevel = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("ball", sf::Vector2f(0.1, 0.1), 2)), RendererComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new PositionComponent(150, 350)), PositionComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new EndLevelTriggerComponent()), TriggerComponent::ID, endLevel);
=======
    EntityCreator::createEnnemyBall(210,250, "ball",compManager, ecs);

    //représentation d'un ennemis (queue) + test trigger attaque
    EntityCreator::createEnnemyCue(330, 450, compManager, ecs );

    //test trigger checkPoint
    EntityCreator::createCheckPoint(200, 50, compManager, ecs);
    EntityCreator::createCheckPoint(300, 400, compManager, ecs);

    //test trigger warp
    EntityCreator::createWarp(100, 350, 260, 0, compManager, ecs);

    //test trigger hole
    EntityCreator::createHole(300, 350, compManager, ecs);

    //test trigger fin de niveau
    EntityCreator::createEndLevel(150, 300, compManager, ecs);
>>>>>>> f036d28b0899a9b01aac85a75fcd24809cc89245


    float dt = 0.0f;
    float time = 0.0f;

	while (window.isOpen())
	{
	    sf::Event event;
	    while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
	    }
		auto startTime = std::chrono::high_resolution_clock::now();

		ecs.updateSystems(dt);
        sf::sleep(sf::milliseconds(20));

		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
		time+=dt;

		cout << time << endl << endl;
	}

    return 0;
}
