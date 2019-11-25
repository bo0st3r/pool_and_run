#ifndef RESPAWNSYSTEM_H
#define RESPAWNSYSTEM_H

#include <System.h>
#include "Configuration/Configuration.h"


class RespawnSystem : public System
{
    public:
        RespawnSystem(  Respawns& r,
                        Characters& c,
                        Positions& p,
                        Velocities& v,
                        Triggers& t);
        virtual ~RespawnSystem();

        virtual void update(float dt);

        bool isPlayerDead();

    protected:

    private:
        bool playerCanRespawn;

        Respawns* respawns;
        Characters* characters;
        Positions* positions;
        Velocities* velocities;
        Triggers* triggers;
};

#endif // RESPAWNSYSTEM_H
