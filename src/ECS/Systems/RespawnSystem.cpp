#include "RespawnSystem.h"

RespawnSystem::RespawnSystem(Respawns& r,
                        Characters& c,
                        Positions& p,
                        Velocities& v,
                        Triggers& t)
{
    respawns = &r;
    characters = &c;
    positions = &p;
    velocities = &v;
    triggers = &t;
}

RespawnSystem::~RespawnSystem()
{
//    delete respawns;
//    delete characters;
//    delete positions;
//    delete velocities;
//    delete triggers;
}

///le respawn system va permettre le respawn du joueur au dernier checkpoint activé en echange d'une vie
///si le joueur n'a plus de vie, le game over s'affiche

void RespawnSystem::update(float dt)
{
    for(Respawns::iterator it = respawns->begin(); it != respawns->cend(); it++)
    {
        Entity entity = it->first;
        CharacterComponent& ch = *(characters->at(entity));
        ch.addLive(-1);
        ComponentManagerSingleton::getInstance()->removeComponentFromEntity(RespawnComponent::ID, entity);

        if(ch.getLive() >= 0)
        {

            for(Triggers::iterator tcIt = triggers->begin(); tcIt != triggers->cend(); tcIt++)
            {
                if(tcIt->second->getTriggerId() == CheckPointTriggerComponent::TRIGGER_ID)
                {
                    Entity triggerEntity = tcIt->first;
                    TriggerComponent& trigger = *(tcIt->second);
                    CheckPointTriggerComponent& checkPoint = dynamic_cast<CheckPointTriggerComponent&> (trigger);
                    if(checkPoint.isLastTriggered()){
                        positions->at(entity)->setPosition(positions->at(triggerEntity)->getPosition());
                        velocities->at(entity)->setVelocity(0, 0);
                    }
                }
            }
        }else
        {
            //si le personnage est un joueur
            if(ch.getTag() == TAG_PLAYER)
            {
                ///GAME OVER
            }else if(ch.getTag() == TAG_ENEMY_BALL || ch.getTag() == TAG_ENEMY_CUE)
            {
                ComponentManagerSingleton::getInstance()->removeAllFromEntity(entity);
                EntityManagerSingleton::getInstance()->deleteEntity(entity);
            }
        }
    }
}
