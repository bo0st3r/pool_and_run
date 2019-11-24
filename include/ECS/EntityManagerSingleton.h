#ifndef ENTITYMANAGERSINGLETON_H
#define ENTITYMANAGERSINGLETON_H

#include <cstdint> //pour les uint
#include <vector>

using Entity = uint32_t; //une entité n'étant représentée que par un ID, on crée un alias d'un entier non signé de 32 bits

class EntityManagerSingleton
{
    public:
        static const Entity MAX_ENTITY = 5000; //nombre maximum d'entités qui pourront être créées

        static EntityManagerSingleton* getInstance(); //renvois l'instance du singleton
        static void releaseInstance();
        virtual ~EntityManagerSingleton(); //destructeur

        Entity createNewEntity(); //ajoute une nouvelle entités à la liste des entité existantes et renvoie cette entité
        int indexOf(Entity entity) const; //donne la position de l'entité passée en argument si elle existe, -1 dans le cas contraire
        void deleteEntity(Entity entity); //retire l'entité de la liste des entité existante
    protected:

    private:
        EntityManagerSingleton(); //crée l'instance du singleton si besoin
        static inline EntityManagerSingleton* instance = 0; //instance du singleton

        static inline Entity nextEntity = 0; //identifiant de la prochaine entité qui sera créée.
        std::vector<Entity> entities; //liste des entités existantes
};

#endif // ENTITYMANAGERSINGLETON_H
