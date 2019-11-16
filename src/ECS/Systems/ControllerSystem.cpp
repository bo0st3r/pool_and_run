#include "ControllerSystem.h"
#include <iostream>

ControllerSystem::ControllerSystem(Velocities& v, Constraints& cons, Controllers& cont)
{

    velocities = &v;
    constraints = &cons;
    controllers = &cont;
}

ControllerSystem::~ControllerSystem()
{

    delete velocities;
    delete constraints;
    delete controllers;
}
void ControllerSystem::update(float dt){

    for(Controllers::iterator it = controllers->begin(); it != controllers->cend(); it++)
    {
        std::cout << "test : ";
        Entity entity = it->first;
        ControllerComponent& controller = *(it->second);
        controller.decreaseDashTime(dt);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                std::cout << "left" << std::endl;
            constraints->at(entity)->removeConstraint(ConstraintEnum::Right);
            velocities->at(entity)->addVelocity(-controller.getSpeed()*dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                std::cout << "right " << controller.getSpeed() << std::endl;
            constraints->at(entity)->removeConstraint(ConstraintEnum::Left);
            velocities->at(entity)->addVelocity(controller.getSpeed()*dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && constraints->at(entity)->hasConstraint(ConstraintEnum::Down)){
            constraints->at(entity)->removeConstraint(ConstraintEnum::Down);
            velocities->at(entity)->addVelocity(0, -controller.getJumpForce());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && controller.getDashTime()<=0){
                std::cout << "dash : remaining " << controller.getDashTime() << std::endl;            controller.resetDashTime();
            if (velocities->at(entity)->getVelocity().x>=0){
                constraints->at(entity)->removeConstraint(ConstraintEnum::Left);
                velocities->at(entity)->addVelocity(controller.getDashSpeed(), 0);
            }else{
                constraints->at(entity)->removeConstraint(ConstraintEnum::Right);
                velocities->at(entity)->addVelocity(-controller.getDashSpeed()*dt, 0);
            }

        }

    }

}


