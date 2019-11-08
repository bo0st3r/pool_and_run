#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"

#include "ECSCoordinatorSingleton.h"
#include "AssetManager.h"
#include "InputManager.h"

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

    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
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
                                        compManager.getEntityConstraintMap()
                                        );
    ecs.addSystem(collisionSystem);
    ecs.addSystem(physicSystem);
    ecs.addSystem(renderSystem);


    //composants de test entité 1
    CharacterComponent& character1 = *(new CharacterComponent("Hero", "Joueur"));
    ColliderComponent& collider1 = *(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false));
    ConstraintComponent& constraint1 = *(new ConstraintComponent());
    PositionComponent& position1 = *(new PositionComponent(0, 0));
    GravityComponent& gravity1 = *(new GravityComponent());
    VelocityComponent& velocity1 = *(new VelocityComponent());
    RendererComponent& render1 = *(new RendererComponent("ball", sf::Vector2f(0.1, 0.1)));

    //composant de test entité 2
    ColliderComponent& collider2 = *(new ColliderComponent(ColliderTypeEnum::Box, false));
    PositionComponent& position2 = *(new PositionComponent(30, 200));
    RendererComponent& render2 = *(new RendererComponent("ball", sf::Vector2f(0.1, 0.1)));


    Entity e1 = ecs.createNewEntity();
    compManager.addComponentToEntity(position1, PositionComponent::ID, e1);
    compManager.addComponentToEntity(gravity1, GravityComponent::ID, e1);
    compManager.addComponentToEntity(velocity1, VelocityComponent::ID, e1);
    compManager.addComponentToEntity(render1, RendererComponent::ID, e1);
    compManager.addComponentToEntity(character1, CharacterComponent::ID, e1);
    compManager.addComponentToEntity(collider1, ColliderComponent::ID, e1);
    compManager.addComponentToEntity(constraint1, ConstraintComponent::ID, e1);

    Entity e2 = ecs.createNewEntity();
    compManager.addComponentToEntity(position2, PositionComponent::ID, e2);
    compManager.addComponentToEntity(collider2, ColliderComponent::ID, e2);
    compManager.addComponentToEntity(render2, RendererComponent::ID, e2);

    float dt = 0.0f;
    float time = 0.0f;

	while (window.isOpen())
	{
	    sf::Event event;
	    while(window.pollEvent(event)){}
		auto startTime = std::chrono::high_resolution_clock::now();

		ecs.updateSystems(dt);
        sf::sleep(sf::milliseconds(20));

		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
		time+=dt;

		cout << time << endl << endl;
	}

    delete &position1;
    delete &gravity1;
    delete &velocity1;
    delete &render1;
    return 0;
}
