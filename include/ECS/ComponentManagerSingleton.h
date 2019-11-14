#ifndef COMPONENTMANAGERSINGLETON_H
#define COMPONENTMANAGERSINGLETON_H

#include <unordered_map>
#include <cstdint>
#include <vector>

#include <EntityManagerSingleton.h>

#include <Component.h>
#include <PositionComponent.h>
#include <VelocityComponent.h>
#include <GravityComponent.h>
#include <RendererComponent.h>
#include <ColliderComponent.h>
#include <TriggerComponent.h>
#include <CheckPointTriggerComponent.h>
#include <CharacterComponent.h>
#include <ConstraintComponent.h>
#include <RespawnComponent.h>

//template pour les association Entité<->Component
template <typename T>
using EntityComponentMap = std::unordered_map<Entity, std::unique_ptr<T>>;

class ComponentManagerSingleton
{
    public:
        static ComponentManagerSingleton* getInstance(); //récupère l'instance du singleton
        virtual ~ComponentManagerSingleton(); //destructeur du singleton

//        template<typename T>
        void addComponentToEntity(Component& component, ComponentID componentId, Entity entity); //ajoute un composant donné à l'entité
        void removeComponentFromEntity(ComponentID component, Entity entity); //retire le composant donné de l'entité
        void removeAllFromEntity(Entity entity); //retire tous les composant de l'entité (avant suppresion de l'entité par exemple)

        EntityComponentMap<PositionComponent>& getEntityPositionMap();
        EntityComponentMap<VelocityComponent>& getEntityVelocityMap();
        EntityComponentMap<GravityComponent>& getEntityGravityMap();
        EntityComponentMap<RendererComponent>& getEntityRendererMap();
        EntityComponentMap<ColliderComponent>& getEntityColliderMap();
        EntityComponentMap<TriggerComponent>& getEntityTriggerMap();
        EntityComponentMap<CharacterComponent>& getEntityCharacterMap();
        EntityComponentMap<ConstraintComponent>& getEntityConstraintMap();
        EntityComponentMap<RespawnComponent>& getEntityRespawnMap();

    protected:

    private:
        ComponentManagerSingleton();//crée l'instance du singleton si besoin
        static inline ComponentManagerSingleton* instance = 0; //instance du singleton

        //ajouter une map par Component possible
        EntityComponentMap<PositionComponent> entityPositions;
        EntityComponentMap<VelocityComponent> entityVelocities;
        EntityComponentMap<GravityComponent> entityGravities;
        EntityComponentMap<RendererComponent> entityRenderers;
        EntityComponentMap<ColliderComponent> entityColliders;
        EntityComponentMap<TriggerComponent> entityTriggers;
        EntityComponentMap<CharacterComponent> entityCharacters;
        EntityComponentMap<ConstraintComponent> entityConstraints;
        EntityComponentMap<RespawnComponent> entityRespawn;
};

#endif // COMPONENTMANAGERSINGLETON_H
