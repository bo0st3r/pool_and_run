#ifndef ENEMY_H
#define ENEMY_H

#include <Character.h>


class Enemy : public Character
{
    public:
        Enemy();
        virtual ~Enemy();
        Enemy(const Enemy& other);

    protected:

    private:
};

#endif // ENEMY_H
