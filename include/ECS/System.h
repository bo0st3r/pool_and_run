#ifndef SYSTEM_H
#define SYSTEM_H

#include <unordered_map>

#include <EntityManagerSingleton.h>
#include <ComponentManagerSingleton.h>

#include <Component.h>
#include <PositionComponent.h>
#include <VelocityComponent.h>
#include <GravityComponent.h>

using Positions = EntityComponentMap<PositionComponent>;
using Velocities = EntityComponentMap<VelocityComponent>;
using Gravities = EntityComponentMap<GravityComponent>;

class System
{
    public:
        virtual void update(float dt)=0; //le system update en tenant compte du temps depuis la dernière update
    protected:

    private:
};

#endif // SYSTEM_H
