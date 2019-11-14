#ifndef CHECKPOINTTRIGGERCOMPONENT_H
#define CHECKPOINTTRIGGERCOMPONENT_H

#include <TriggerComponent.h>


class CheckPointTriggerComponent : public TriggerComponent
{
    public:
        CheckPointTriggerComponent();
        virtual ~CheckPointTriggerComponent();
        static inline const ComponentID TRIGGER_ID = 500;

        virtual ComponentID getTriggerId() const;
        bool isLastTriggered() const;
        void setLastTriggered(bool lastTriggered);

        virtual void onTrigger(Entity , std::string tag);

    protected:

    private:
        bool lastTriggered;
};

#endif // CHECKPOINTTRIGGERCOMPONENT_H
