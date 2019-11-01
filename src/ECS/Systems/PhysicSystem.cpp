#include "PhysicSystem.h"

#include<iostream>

PhysicSystem::PhysicSystem(Positions& p, Velocities& v, Gravities& g)
{
    positions = &p;
    velocities = &v;
    gravities = &g;
}

PhysicSystem::~PhysicSystem()
{
    delete positions;
    delete velocities;
    delete gravities;
}

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
    positions->at(entity).translate(velocities->at(entity).getVx() * dt, velocities->at(entity).getVy() * dt);
    std::cout << "debug position PhysicSystem Ligne 43 : " << positions->at(entity).str() << std::endl;
}
