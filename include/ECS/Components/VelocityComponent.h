#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <Component.h>


class VelocityComponent : public Component
{
    public:
        VelocityComponent();
        virtual ~VelocityComponent();

        static inline const ComponentID ID = 1;

        float getVx() const;
        float getVy() const;
        virtual ComponentID getTypeId() const;
        static ComponentID getId(){return ID;};
        void setVx(float vx);
        void setVy(float vy);

        void addVelocity(float dvx, float dvy);
        void setVelocity(float vx, float vy);

        virtual std::string str() const;


    protected:

    private:
        float vx;
        float vy;
};

#endif // VELOCITYCOMPONENT_H
