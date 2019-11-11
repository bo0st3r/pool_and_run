#ifndef ENDLEVELTRIGGERCOMPONENT_H
#define ENDLEVELTRIGGERCOMPONENT_H

#include <TriggerComponent.h>


class EndLevelTriggerComponent : public TriggerComponent
{
    public:
        EndLevelTriggerComponent();
        virtual ~EndLevelTriggerComponent();
        static inline const ComponentID TRIGGER_ID = 501;

        virtual ComponentID getTriggerId() const;

        virtual void onTrigger(Entity , std::string tag);


    protected:

    private:
};

#endif // ENDLEVELTRIGGERCOMPONENT_H
