#ifndef PLAYER_H
#define PLAYER_H

#include <Character.h>


class Player : public Character
{
    public:
        Player();
        virtual ~Player();
        Player(const Player& other);

    protected:

    private:
};

#endif // PLAYER_H
