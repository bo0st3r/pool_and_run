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
                                        window.getSize()
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
                                                compManager.getEntityVelocityMap()
                                                );
    ecs.addSystem(collisionSystem);
    ecs.addSystem(triggerSystem);
    ecs.addSystem(physicSystem);
    ecs.addSystem(renderSystem);
    ecs.addSystem(respawnSystem);

    //représentation du joueur
    EntityCreator::createPlayer(200,0, "ball",compManager, ecs);
    EntityCreator::createPlayer(300,50, "ball",compManager, ecs);



    //représentation des plateforme
    EntityCreator::createTile(200,300, "ball",compManager, ecs);
    EntityCreator::createTile(300,500, "ball",compManager, ecs);

    //représentation d'un ennemis (boule)
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
