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

//    delete velocities;
//    delete constraints;
//    delete controllers;
}
void ControllerSystem::update(float dt){

    for(Controllers::iterator it = controllers->begin(); it != controllers->cend(); it++)
    {
        Entity entity = it->first;
        ControllerComponent& controller = *(it->second);
        controller.decreaseDashTime(dt);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            constraints->at(entity)->removeConstraint(ConstraintEnum::Right);
            velocities->at(entity)->addVelocity(-controller.getSpeed()*dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            constraints->at(entity)->removeConstraint(ConstraintEnum::Left);
            velocities->at(entity)->addVelocity(controller.getSpeed()*dt, 0);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && constraints->at(entity)->hasConstraint(ConstraintEnum::Down)){
            constraints->at(entity)->removeConstraint(ConstraintEnum::Down);
            velocities->at(entity)->addVelocity(0, -controller.getJumpForce());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && controller.getDashTime()<=0){            controller.resetDashTime();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                constraints->at(entity)->removeConstraint(ConstraintEnum::Right);
                velocities->at(entity)->addVelocity(-controller.getDashSpeed(), 0);
            }else{
                constraints->at(entity)->removeConstraint(ConstraintEnum::Left);
                velocities->at(entity)->addVelocity(controller.getDashSpeed(), 0);
            }

        }

    }

}


