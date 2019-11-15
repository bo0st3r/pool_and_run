#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include <System.h>


class ControllerSystem : public System
{
    public:
        ControllerSystem(Velocities& v, Constraints& cons, Controllers& cont);
        virtual ~ControllerSystem();

        virtual void update(float dt);


    protected:

    private:

        Velocities* velocities;
        Constraints* constraints;
        Controllers* controllers;

};

#endif // CONTROLLERSYSTEM_H
