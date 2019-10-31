#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <Component.h>


class VelocityComponent : public Component
{
    public:
        VelocityComponent();
        virtual ~VelocityComponent();

        float getVx() const;
        float getVy() const;
        virtual ComponentID getTypeId() const;
        static ComponentID getId(){return id;};
        void setVx(float vx);
        void setVy(float vy);

        void addVelocity(float dvx, float dvy);
        void setVelocity(float vx, float vy);

        virtual std::string str() const;


    protected:

    private:
        float vx;
        float vy;
        static inline ComponentID id = 1;
};

#endif // VELOCITYCOMPONENT_H
