#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#include <Component.h>


class ControllerComponent : public Component
{
    public:
        ControllerComponent(float speed=0, float jumpForce=0, float dashSpeed=0, float dashDelay=5);
        virtual ~ControllerComponent();

        virtual ComponentID getTypeId() const;
        float getSpeed()const;
        float getJumpForce()const;
        float getDashSpeed()const;
        float getDashTime()const;

        void decreaseDashTime(float time);
        void resetDashTime();

        virtual std::string str() const;

        static inline const ComponentID ID = 9;


    protected:

    private:
        float speed;
        float jumpForce;
        float dashSpeed;
        float dashDelay;
        float dashTime;
};

#endif // CONTROLLERCOMPONENT_H
