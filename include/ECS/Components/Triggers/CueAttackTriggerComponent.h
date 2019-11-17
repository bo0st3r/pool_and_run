#ifndef CUEATTAQUETRIGGERCOMPONENT_H
#define CUEATTAQUETRIGGERCOMPONENT_H

#include <TriggerComponent.h>


class CueAttackTriggerComponent : public TriggerComponent
{
    public:
        CueAttackTriggerComponent();
        virtual ~CueAttackTriggerComponent();
        static inline const ComponentID TRIGGER_ID = 504;
        static inline const float SPEED_CAP = 200;
        static inline const float BUMP_SPEED = 300;

        virtual ComponentID getTriggerId() const;
        Entity getTargetEntity() const;

        void setTargetEntity(Entity entity);

        virtual void onTrigger(Entity , std::string tag);


    protected:

    private:
        Entity targetEntity = EntityManagerSingleton::MAX_ENTITY;
};

#endif // CUEATTAQUETRIGGERCOMPONENT_H
