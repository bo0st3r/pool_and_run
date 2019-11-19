#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H

#include "Configuration/Configuration.h"

#include <System.h>


class TriggerSystem : public System
{
    public:
        TriggerSystem(Triggers& t, Positions& p, Velocities& v, Renderers& r, Characters& c);
        virtual ~TriggerSystem();

        virtual void update(float dt);

        void checkPointTriggered(Entity entity, CheckPointTriggerComponent& checkPoint);
        void cueAttackTriggered(Entity entity, CueAttackTriggerComponent& cueAttack);
        void endLevelTriggered(Entity entity, EndLevelTriggerComponent& endLevel);
        void holeTriggered(Entity entity, HoleTriggerComponent& hole);
        void warpTriggered(Entity entity, WarpTriggerComponent& warp);

        int remainingBalls();

    protected:

    private:
        Triggers* triggers;
        Positions* positions;
        Velocities* velocities;
        Renderers* renderers;
        Characters* characters;
};

#endif // TRIGGERSYSTEM_H
