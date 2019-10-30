#include "ComponentManagerSingleton.h"

ComponentManagerSingleton::ComponentManagerSingleton()
{}

ComponentManagerSingleton::~ComponentManagerSingleton()
{
    delete instance;
}

ComponentManagerSingleton* ComponentManagerSingleton::getInstance()
{
    if(instance == 0)
    {
        instance = new ComponentManagerSingleton();
    }

    return instance;
}

void ComponentManagerSingleton::addComponent(ComponentID component)
{
    maps.push_back(EntityComponentMap());
    componentIndexes.insert(std::pair<ComponentID, int>(component, maps.size()-1));
}

void ComponentManagerSingleton::addComponentToEntity(Component& component, Entity entity)
{
    //récupère l'index de la map de liaison dans le tableau grace à la map d'index
    int index = componentIndexes.at(component.getTypeId());
    //récupère la map dans le tableau grace à l'index
    EntityComponentMap& linkMap = maps[index];

    //ajoute le lien entity-component dans la map si il n'y est pas deja
    if(linkMap.find(entity) != linkMap.end())
    {
        linkMap.insert(std::pair<Entity, Component&>(entity, component));
    }
}

void ComponentManagerSingleton::removeComponentFromEntity(ComponentID component, Entity entity)
{
    //récupère l'index de la map de liaison dans le tableau grace à la map d'index
    int index = componentIndexes.at(component);
    //récupère la map dans le tableau grace à l'index
    EntityComponentMap& linkMap = maps[index];

    //essaye de supprimer le lien entity-component de la map
    linkMap.erase(entity);
}

void ComponentManagerSingleton::removeAllFromEntity(Entity entity)
{
    for(EntityComponentMap linkMap : maps)
    {
        linkMap.erase(entity);
    }
}

EntityComponentMap& ComponentManagerSingleton::getEntityComponentMap(ComponentID component)
{
    //récupère l'index de la map de liaison dans le tableau grace à la map d'index
    int index = componentIndexes.at(component);
    //récupère la map dans le tableau grace à l'index
    return maps[index];

}
