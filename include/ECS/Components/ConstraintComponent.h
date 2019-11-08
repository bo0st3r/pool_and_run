#ifndef CONSTRAINTCOMPONENT_H
#define CONSTRAINTCOMPONENT_H

#include <Component.h>
#include <ConstraintEnum.h>

class ConstraintComponent : public Component
{
    public:
        ConstraintComponent(std::vector<ConstraintEnum> constraints = std::vector<ConstraintEnum>());
        virtual ~ConstraintComponent();

        virtual ComponentID getTypeId() const;
        std::vector<ConstraintEnum> getConstraints() const;

        void addConstraint(ConstraintEnum constraint);
        void removeConstraint(ConstraintEnum constraint);

        static inline const ComponentID ID = 7;

        virtual std::string str() const;


    protected:

    private:
        std::vector<ConstraintEnum> constraints;
};

#endif // CONSTRAINTCOMPONENT_H
