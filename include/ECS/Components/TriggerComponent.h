#ifndef TRIGGERCOMPONENT_H
#define TRIGGERCOMPONENT_H

#include <Component.h>

class TriggerComponent : public Component
{
    public:
        TriggerComponent();
        virtual ~TriggerComponent();
        virtual ComponentID getTypeId() const;

        static inline const ComponentID ID = 5;

        virtual void onTrigger(Entity entity) = 0;

        virtual std::string str() const;

    protected:

    private:
};

#endif // TRIGGERCOMPONENT_H
