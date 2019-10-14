#ifndef CHARACTER_H
#define CHARACTER_H

#include <LevelElement.h>


class Character : public LevelElement
{
    public:
        Character();
        virtual ~Character();
        Character(const Character& other);

    protected:

    private:
};

#endif // CHARACTER_H
