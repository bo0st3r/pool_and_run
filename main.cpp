#include <SFML/Graphics.hpp>

#include <ECSCoordinatorSingleton.h>
#include <chrono>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

int main()
{
    // Getting instances of ECS Coordinator and ComponenManager singletons
    ECSCoordinatorSingleton& ecs = *(ECSCoordinatorSingleton::getInstance());
    ComponentManagerSingleton& compManager = *(ComponentManagerSingleton::getInstance());

    //ajout des systemes
    PhysicSystem physic = PhysicSystem(
                                        compManager.getEntityPositionMap(),
                                        compManager.getEntityVelocityMap(),
                                        compManager.getEntityGravityMap()
                                       );
    ecs.addSystem(physic);



    PositionComponent& position = *(new PositionComponent(500, 8000));
    GravityComponent& gravity = *(new GravityComponent());
    VelocityComponent& velocity = *(new VelocityComponent());

    Entity e1 = ecs.createNewEntity();
    compManager.addComponentToEntity(position, PositionComponent::ID, e1);
    compManager.addComponentToEntity(gravity, GravityComponent::ID, e1);
    compManager.addComponentToEntity(velocity, VelocityComponent::ID, e1);



    float dt = 0.0f;
    float time = 0.0f;

	while (time < 2)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		ecs.updateSystems(dt);
//		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
		time+=dt;

		cout << time << endl << endl;
	}

    delete &position, &gravity, &velocity;
    return 0;
}
