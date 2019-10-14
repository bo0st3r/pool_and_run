#ifndef POOLCUE_H
#define POOLCUE_H

#include <Enemy.h>


class PoolCue : public Enemy
{
    public:
        PoolCue();
        virtual ~PoolCue();
        PoolCue(const PoolCue& other);

    protected:

    private:
};

#endif // POOLCUE_H
