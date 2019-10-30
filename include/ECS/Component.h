#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>
#include <sstream>
#include <string>

using ComponentID = uint32_t;

class Component
{
    public:
        virtual ComponentID getTypeId() const = 0;

    protected:

    private:
};

#endif // COMPONENT_H
