#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <LevelElement.h>
#include <ITriggerableElement.h>


class CheckPoint : public LevelElement, public ITriggerableElement
{
    public:
        CheckPoint();
        virtual ~CheckPoint();
        CheckPoint(const CheckPoint& other);
        void OnTrigger();

    protected:

    private:
};

#endif // CHECKPOINT_H
