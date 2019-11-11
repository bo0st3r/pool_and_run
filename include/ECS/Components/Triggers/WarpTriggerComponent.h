#ifndef WARPTRIGGERCOMPONENT_H
#define WARPTRIGGERCOMPONENT_H

#include <TriggerComponent.h>


class WarpTriggerComponent : public TriggerComponent
{
    public:
        WarpTriggerComponent(sf::Vector2f destination = sf::Vector2f(0, 0), bool exitToRight = true);
        virtual ~WarpTriggerComponent();
        static inline const ComponentID TRIGGER_ID = 502;

        virtual ComponentID getTriggerId() const;
        sf::Vector2f getDestination()const;
        bool isExitToRight() const;
        Entity getTargetEntity() const;

        void setTargetEntity(Entity entity);

        virtual void onTrigger(Entity , std::string tag);

    protected:

    private:
        sf::Vector2f destination;
        bool exitToRight;
        Entity targetEntity = EntityManagerSingleton::MAX_ENTITY;
};

#endif // WARPTRIGGERCOMPONENT_H
