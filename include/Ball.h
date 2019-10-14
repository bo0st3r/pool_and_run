#ifndef BALL_H
#define BALL_H

#include <Enemy.h>


class Ball : public Enemy
{
    public:
        Ball();
        virtual ~Ball();
        Ball(const Ball& other);

    protected:

    private:
};

#endif // BALL_H
