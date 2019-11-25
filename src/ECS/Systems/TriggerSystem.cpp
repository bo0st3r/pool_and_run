#include "TriggerSystem.h"
#include <iostream>

TriggerSystem::TriggerSystem(Triggers& t, Positions& p, Velocities& v, Renderers& r, Characters& c)
{
    triggers = &t;
    positions = &p;
    velocities = &v;
    renderers = &r;
    characters = &c;

    playerHasWon = false;
}

TriggerSystem::~TriggerSystem()
{
//    delete triggers;
//    delete positions;
//    delete velocities;
//    delete renderers;
//    delete characters;
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
                    cueAttackTriggered(entity, cueAttack);
                    break;
                }
                case EndLevelTriggerComponent::TRIGGER_ID:{
                    EndLevelTriggerComponent& endLevel = dynamic_cast<EndLevelTriggerComponent&>(trigger);
                    endLevelTriggered(entity, endLevel);
                    break;
                }
                case HoleTriggerComponent::TRIGGER_ID:{
                    HoleTriggerComponent& hole = dynamic_cast<HoleTriggerComponent&>(trigger);
                    holeTriggered(entity, hole);
                    break;
                }
                case WarpTriggerComponent::TRIGGER_ID:{
                    WarpTriggerComponent& warp = dynamic_cast<WarpTriggerComponent&>(trigger);
                    warpTriggered(entity, warp);
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

void TriggerSystem::cueAttackTriggered(Entity entity, CueAttackTriggerComponent& cueAttack)
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
        sf::Vector2f normalizedDirection = Vector2fMath::normalize(Vector2fMath::directionBetween(positions->at(entity)->getPosition(), positions->at(other)->getPosition()));
        float bumpSpeed = CueAttackTriggerComponent::BUMP_SPEED;
        sf::Vector2f newVelocity = sf::Vector2f(bumpSpeed * normalizedDirection.x, bumpSpeed * normalizedDirection.y);

        velocities->at(other)->setVelocity(newVelocity);
    }

    cueAttack.setTriggered(false);
    cueAttack.setTargetEntity(EntityManagerSingleton::MAX_ENTITY);
}

void TriggerSystem::endLevelTriggered(Entity entity, EndLevelTriggerComponent& endLevel)
{
    if(remainingBalls() == 0)
    {
        playerHasWon = true;
    }
    endLevel.setTriggered(false);
}

bool TriggerSystem::hasPlayerWon(){
    return playerHasWon;
}

void TriggerSystem::holeTriggered(Entity entity, HoleTriggerComponent& hole)
{
    ComponentManagerSingleton& compManager = *(ComponentManagerSingleton::getInstance());

    Entity other = hole.getTargetEntity();

    compManager.addComponentToEntity(*(new RespawnComponent()), RespawnComponent::ID, other);

    hole.setTriggered(false);
    hole.setTargetEntity(EntityManagerSingleton::MAX_ENTITY);
}

void TriggerSystem::warpTriggered(Entity entity, WarpTriggerComponent& warp)
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

int TriggerSystem::remainingBalls()
{
    int remaining = 0;
    for(Characters::iterator it = characters->begin(); it != characters->cend(); it++)
    {
        CharacterComponent& character = *(it->second);
        if(character.getTag() == TAG_ENEMY_BALL)
        {
            remaining++;
        }
    }

    return remaining;
}
