#include "PhysicSystem.h"

#include<iostream>

PhysicSystem::PhysicSystem(Positions& p, Velocities& v, Gravities& g, Constraints& c)
{
    positions = &p;
    velocities = &v;
    gravities = &g;
    constraints = &c;
}

PhysicSystem::~PhysicSystem()
{
    delete positions;
    delete velocities;
    delete gravities;
    delete constraints;
}


///Le physicSystem va permettre la gestion de la partie physique du jeu
///en particulier l'application de forces sur les entités ainsi que leurs calculs de déplacement
void PhysicSystem::update(float dt)
{
    for(Positions::iterator it = positions->begin(); it != positions->cend(); it++)
    {
        Entity entity = it->first;

        if(velocities->find(entity) != velocities->cend())
        {
            if(gravities->find(entity) != gravities->cend())
            {
                addGravityToVelocity(entity, dt);
            }
            if(constraints->find(entity) != constraints->cend())
            {
                applyConstraints(entity);
            }

            addVelocityToPosition(entity, dt);
        }
    }
}

void PhysicSystem::addGravityToVelocity(Entity entity, float dt)
{
    velocities->at(entity).addVelocity(0, GravityComponent::getG() * dt);
}

void PhysicSystem::addVelocityToPosition(Entity entity, float dt)
{
    positions->at(entity).translate(velocities->at(entity).getVelocity() * dt);
    std::cout << "debug position PhysicSystem Ligne 43 : " << positions->at(entity).str() << std::endl;
}

void PhysicSystem::applyConstraints(Entity entity)
{
    std::vector<ConstraintEnum> constraintVect = constraints->at(entity).getConstraints();
    float vy = velocities->at(entity).getVelocity().y;
    float vx = velocities->at(entity).getVelocity().x;


    for(ConstraintEnum constraint : constraintVect)
    {
        switch (constraint){
            case ConstraintEnum::Down:{
                if(vy < 0)
                {
                    velocities->at(entity).addVelocity(0, -vy);
                }
                break;
            }
            case ConstraintEnum::Left:{
                if(vx < 0)
                {
                    velocities->at(entity).addVelocity(-vx, 0);
                }
                break;
            }case ConstraintEnum::Up:{
                if(vy > 0)
                {
                    velocities->at(entity).addVelocity(0, -vy);
                }
                break;
            }case ConstraintEnum::Right:{
                if(vx > 0)
                {
                    velocities->at(entity).addVelocity(-vx, 0);
                }
                break;
            }
        }
    }
}
