#include "Level.h"

Level::Level(string name):name(name)
{
    this->id = new int(++lastId);
}

Level::~Level()
{
    delete id;
}

Level::Level(const Level& other):name(other.name)
{
    this->id = new int(++lastId);
}
