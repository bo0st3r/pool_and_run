#ifndef ECSCOORDINATORSINGLETON_H
#define ECSCOORDINATORSINGLETON_H

#include <EntityManagerSingleton.h>
#include <ComponentManagerSingleton.h>
#include <SystemManagerSingleton.h>

class ECSCoordinatorSingleton
{
    public:
        static ECSCoordinatorSingleton* getInstance();
        virtual ~ECSCoordinatorSingleton();

        Entity createNewEntity(); //crée une nouvelle entité et la renvoie pour utilisation
        void removeEntity(Entity entity); //supprime une Entité du système

        template <typename T>
        void addComponent(ComponentID component); //ajoute un component qui sera utilisé lors de l'execution
        void addComponenntToEntity(Component& component, Entity entity); //crée un nouveau component pour l'entité donnée
        void removeComponentFromEntity(ComponentID component, Entity entity); //retire le component de l'entité
        EntityComponentMap<Component>* getEntityComponentMap(ComponentID component); //recupère la map d'association d'un component

        void addSystem(System& system); //ajoute un systeme à executé lors de l'execution /!\ ajouter dans l'ordre d'execution voulu /!\//
        void updateSystems(float dt); //met à jour les systeme en leur disant le temps ecouler depuis la dernière update

    protected:

    private:
        ECSCoordinatorSingleton();

        static inline ECSCoordinatorSingleton* instance = 0;

        EntityManagerSingleton* entityManager = EntityManagerSingleton::getInstance();
        ComponentManagerSingleton* componentManager = ComponentManagerSingleton::getInstance();
        SystemManagerSingleton* systemManager = SystemManagerSingleton::getInstance();
};

#endif // ECSCOORDINATORSINGLETON_H
