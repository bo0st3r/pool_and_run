#include "ConstraintComponent.h"

ConstraintComponent::ConstraintComponent(std::vector<ConstraintEnum> constraints)
:constraints(constraints)
{}

ConstraintComponent::~ConstraintComponent()
{}

ComponentID ConstraintComponent::getTypeId() const
{
    return ID;
}

std::vector<ConstraintEnum> ConstraintComponent::getConstraints() const
{
    return constraints;
}

bool ConstraintComponent::hasConstraint(ConstraintEnum constraint) const
{
    for(int i = 0; i < constraints.size(); i++)
    {
        if(constraints[i] == constraint)
        {
            return true;
        }
    }

    return false;
}

void ConstraintComponent::addConstraint(ConstraintEnum constraint)
{
    if(std::find(constraints.begin(), constraints.end(), constraint) == constraints.end())
    {
        constraints.push_back(constraint);
    }
}

void ConstraintComponent::removeConstraint(ConstraintEnum constraint)
{
    std::vector<ConstraintEnum>::iterator vectConstraint = std::find(constraints.begin(), constraints.end(), constraint);
    if(vectConstraint != constraints.end())
    {
        constraints.erase(vectConstraint);
    }
}

std::string ConstraintComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (constraint) : ";
    for(ConstraintEnum constraint : constraints)
    {
        sstr << constraint << ", ";
    }
    return sstr.str();
}
