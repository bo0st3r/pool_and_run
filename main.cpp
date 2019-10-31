#include <SFML/Graphics.hpp>

#include <ECSCoordinatorSingleton.h>

int main()
{
    /*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    */

    ECSCoordinatorSingleton ecs = *ECSCoordinatorSingleton::getInstance();

    Entity e1 = ecs.createNewEntity();

    //ajout des components
    ecs.addComponent<PositionComponent>(PositionComponent::getId());
    ecs.addComponent<VelocityComponent>(VelocityComponent::getId());
    ecs.addComponent<GravityComponent>(GravityComponent::getId());

    //ajout des systemes
    PhysicSystem physic = PhysicSystem(
                                        *ecs.getEntityComponentMap(PositionComponent::getId()),
                                        *ecs.getEntityComponentMap(VelocityComponent::getId()),
                                        *ecs.getEntityComponentMap(GravityComponent::getId())
                                       );

    ecs.addComponenntToEntity(*(new PositionComponent(0, 0)), e1);
    ecs.addComponenntToEntity(*(new GravityComponent()), e1);
    ecs.addComponenntToEntity(*(new VelocityComponent()), e1);

    ecs.addSystem(physic);



    return 0;
}
