#ifndef BALLHOLE_H
#define BALLHOLE_H

#include <LevelElement.h>
#include <ITriggerableElement.h>


class BallHole : public LevelElement, public ITriggerableElement
{
    public:
        BallHole();
        virtual ~BallHole();
        BallHole(const BallHole& other);

    protected:

    private:
};

#endif // BALLHOLE_H
