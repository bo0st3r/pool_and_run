#include "ControllerComponent.h"

ControllerComponent::ControllerComponent(float speed, float jumpForce, float dashSpeed, float dashDelay)
:speed(speed), jumpForce(jumpForce), dashSpeed(dashSpeed), dashDelay(dashDelay)
{
    //ctor
}

ControllerComponent::~ControllerComponent()
{
    //dtor
}
ComponentID ControllerComponent::getTypeId() const
{
    return ID;
}

float ControllerComponent::getSpeed()const{
    return speed;
}

float ControllerComponent::getJumpForce()const{
    return jumpForce;
}

float ControllerComponent::getDashSpeed()const{
    return dashSpeed;
}

float ControllerComponent::getDashTime()const{
    return dashTime;
}

void ControllerComponent::decreaseDashTime(float time){
    dashTime-=time;
}
void ControllerComponent::resetDashTime(){
    dashTime = dashDelay;
}

std::string ControllerComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (controller)";
    return sstr.str();
}
