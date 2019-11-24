#include "EntityManagerSingleton.h"
#include <iostream>


EntityManagerSingleton::EntityManagerSingleton()
{
    std::cout << "entity" << std::endl;
}

EntityManagerSingleton::~EntityManagerSingleton()
{
    //dtor
}

void EntityManagerSingleton::releaseInstance(){
    delete instance;
    instance = 0;
}


EntityManagerSingleton* EntityManagerSingleton::getInstance()
{
    //crée l'instance du singleton si elle n'existe pas encore
    if(instance == 0)
    {
        instance = new EntityManagerSingleton();
    }

    return instance;
}

Entity EntityManagerSingleton::createNewEntity()
{
    if(nextEntity < MAX_ENTITY) //ajoute l'ID suivant si possible
    {
        entities.push_back(nextEntity++);
        return (nextEntity - 1);
    }
    /*si l'ID suivant est le maximum mais qu'il n'y a pas le maximum d'entité dans la liste,
        on parcours cette liste pour trouvé le premier ID libre
    */
    else if(entities.size() < MAX_ENTITY)
    {
        for(uint32_t i = 0; i < entities.size(); i++)
        {
            if(entities[i] != i)
            {
                std::vector<Entity>::iterator it = entities.begin();
                entities.insert(it + i, i);
                return i;
            }
        }
    }

    return MAX_ENTITY;
}

int EntityManagerSingleton::indexOf(Entity entity) const
{
    for(int i = 0; i < entities.size(); i++)
    {
        if(entities[i] == entity)
        {
            return i;
        }
    }

    return -1;
}

void EntityManagerSingleton::deleteEntity(Entity entity)
{
    int index = indexOf(entity);
    if(index > -1)
    {
        //si l'entité est la dernière ajoutée, on décrémente nextEntity
        if(index == (entities.size()-1))
        {
            entities.pop_back();
            nextEntity--;
        }else //on laisse un trou qui sera comblé plus tard
        {
            std::vector<Entity>::iterator it = entities.begin();
            entities.erase(it+index);
        }
    }
}

