#ifndef CHECKPOINTTRIGGERCOMPONENT_H
#define CHECKPOINTTRIGGERCOMPONENT_H

#include <TriggerComponent.h>


class CheckPointTriggerComponent : public TriggerComponent
{
    public:
        CheckPointTriggerComponent();
        virtual ~CheckPointTriggerComponent();

        virtual void onTrigger(Entity entity);

    protected:

    private:
};

#endif // CHECKPOINTTRIGGERCOMPONENT_H
