#ifndef WARP_H
#define WARP_H

#include <LevelElement.h>
#include <ITriggerableElement.h>


class Warp : public LevelElement, public ITriggerableElement
{
    public:
        Warp();
        virtual ~Warp();
        Warp(const Warp& other);
        void OnTrigger();

    protected:

    private:
};

#endif // WARP_H
