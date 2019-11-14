#ifndef HOLETRIGGERCOMPONENT_H
#define HOLETRIGGERCOMPONENT_H

#include <TriggerComponent.h>


class HoleTriggerComponent : public TriggerComponent
{
    public:
        HoleTriggerComponent(std::string targetTag);
        virtual ~HoleTriggerComponent();
        static inline const ComponentID TRIGGER_ID = 503;

        virtual ComponentID getTriggerId() const;
        std::string getTargetTag() const;
        Entity getTargetEntity() const;

        void setTargetEntity(Entity entity);

        virtual void onTrigger(Entity , std::string tag);


    protected:

    private:
        std::string targetTag;
        Entity targetEntity = EntityManagerSingleton::MAX_ENTITY;
};

#endif // HOLETRIGGERCOMPONENT_H
