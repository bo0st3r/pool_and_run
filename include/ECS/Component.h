#ifndef COMPONENT_H
#define COMPONENT_H

#include <algorithm>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>
#include <SFML/System.hpp>

#include <EntityManagerSingleton.h>
#include <ColliderTypeEnum.h>
#include <ConstraintEnum.h>

using ComponentID = uint32_t;

class Component
{
    public:
        virtual ComponentID getTypeId() const = 0;

    protected:

    private:
};

#endif // COMPONENT_H
