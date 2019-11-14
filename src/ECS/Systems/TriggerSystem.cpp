#include "TriggerSystem.h"

TriggerSystem::TriggerSystem(Triggers& t, Positions& p, Velocities& v, Renderers& r)
{
    triggers = &t;
    positions = &p;
    velocities = &v;
    renderers = &r;
}

TriggerSystem::~TriggerSystem()
{
    delete triggers;
    delete positions;
    delete velocities;
    delete renderers;
}

void TriggerSystem::update(float dt)
{
    ComponentManagerSingleton& compManager = *(ComponentManagerSingleton::getInstance());

    for(Triggers::iterator it = triggers->begin(); it != triggers->cend(); it++)
    {
        Entity entity = it->first;
        TriggerComponent& trigger = *(it->second);

        if(trigger.isTriggered())
        {
            switch(trigger.getTriggerId())
            {
                ///on remplace le checkpoint actif par le nouveau en desactivant les autres
                case CheckPointTriggerComponent::TRIGGER_ID:{
                    CheckPointTriggerComponent& checkPoint = dynamic_cast<CheckPointTriggerComponent&>(trigger);
                    checkPointTriggered(entity, checkPoint);
                    break;
                }
                case CueAttackTriggerComponent::TRIGGER_ID:{
                    CueAttackTriggerComponent& cueAttack = dynamic_cast<CueAttackTriggerComponent&>(trigger);
                    CueAttackTriggered(entity, cueAttack);
                    break;
                }
                case EndLevelTriggerComponent::TRIGGER_ID:{
                    EndLevelTriggerComponent& endLevel = dynamic_cast<EndLevelTriggerComponent&>(trigger);
                    EndLevelTriggered(entity, endLevel);
                    break;
                }
                case HoleTriggerComponent::TRIGGER_ID:{
                    HoleTriggerComponent& hole = dynamic_cast<HoleTriggerComponent&>(trigger);
                    HoleTriggered(entity, hole);
                    break;
                }
                case WarpTriggerComponent::TRIGGER_ID:{
                    WarpTriggerComponent& warp = dynamic_cast<WarpTriggerComponent&>(trigger);
                    WarpTriggered(entity, warp);
                    break;
                }
            }
        }
    }
}

void TriggerSystem::checkPointTriggered(Entity entity, CheckPointTriggerComponent& checkPoint)
{
    for(Triggers::iterator cp = triggers->begin(); cp != triggers->cend(); cp++)
    {
        if(cp->first != entity && cp->second->getTriggerId() == CheckPointTriggerComponent::TRIGGER_ID)
        {
            CheckPointTriggerComponent& checkPoint2 = dynamic_cast<CheckPointTriggerComponent&>(*(cp->second));
            checkPoint2.setLastTriggered(false);
        }
    }

    checkPoint.setTriggered(false);
    checkPoint.setLastTriggered(true);

}

void TriggerSystem::CueAttackTriggered(Entity entity, CueAttackTriggerComponent& cueAttack)
{
    ComponentManagerSingleton& compManager = *(ComponentManagerSingleton::getInstance());

    Entity other = cueAttack.getTargetEntity();
    float otherSpeed = Vector2fMath::magnitude(velocities->at(other)->getVelocity());

    //si le joueur arrive trop vite (vitesse atteignable uniquement via un dash), tue l'ennemis
    if(otherSpeed > CueAttackTriggerComponent::SPEED_CAP)
    {
        compManager.addComponentToEntity(*(new RespawnComponent()), RespawnComponent::ID, entity);
    }else //pousse violemment le joueur dans la direction opposée
    {
        float angle = Vector2fMath::angleBetween(positions->at(entity)->getPosition(), positions->at(other)->getPosition());
        float bumpSpeed = CueAttackTriggerComponent::BUMP_SPEED;
        sf::Vector2f newVelocity = sf::Vector2f(bumpSpeed * std::sin(angle), bumpSpeed * std::cos(angle));

        velocities->at(other)->setVelocity(newVelocity);
    }

    cueAttack.setTriggered(false);
    cueAttack.setTargetEntity(EntityManagerSingleton::MAX_ENTITY);
}

void TriggerSystem::EndLevelTriggered(Entity entity, EndLevelTriggerComponent& endLevel)
{
    endLevel.setTriggered(false);
}

void TriggerSystem::HoleTriggered(Entity entity, HoleTriggerComponent& hole)
{
    ComponentManagerSingleton& compManager = *(ComponentManagerSingleton::getInstance());

    Entity other = hole.getTargetEntity();

    compManager.addComponentToEntity(*(new RespawnComponent()), RespawnComponent::ID, other);

    hole.setTriggered(false);
    hole.setTargetEntity(EntityManagerSingleton::MAX_ENTITY);
}

void TriggerSystem::WarpTriggered(Entity entity, WarpTriggerComponent& warp)
{
    sf::Vector2 exit = warp.getDestination();
    float warpWidth = renderers->at(entity)->getSpriteRef().getGlobalBounds().width;
    Entity other = warp.getTargetEntity();
    float otherWidth = renderers->at(other)->getSpriteRef().getGlobalBounds().width;

    if(warp.isExitToRight())
    {
        positions->at(other)->setPosition(exit + sf::Vector2f(warpWidth, 0));
    }else
    {
        positions->at(other)->setPosition(exit - sf::Vector2f(otherWidth, 0));
    }
    velocities->at(other)->setVelocity(0, 0);

    warp.setTriggered(false);
    warp.setTargetEntity(EntityManagerSingleton::MAX_ENTITY);
}
