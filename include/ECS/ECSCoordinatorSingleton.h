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

        void removeComponentFromEntity(ComponentID component, Entity entity); //retire le component de l'entité

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
