#ifndef TRIGGERCOMPONENT_H
#define TRIGGERCOMPONENT_H

#include <Component.h>

class TriggerComponent : public Component
{
    public:
        TriggerComponent();
        virtual ~TriggerComponent();
        virtual ComponentID getTypeId() const;
        virtual ComponentID getTriggerId() const = 0;

        static inline const ComponentID ID = 5;
        bool isTriggered() const;

        void setTriggered(bool triggered);

        virtual void onTrigger(Entity entity, std::string tag) = 0;

        virtual std::string str() const;

    protected:

    private:
        bool triggered;
};

#endif // TRIGGERCOMPONENT_H
