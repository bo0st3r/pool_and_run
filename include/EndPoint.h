#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <LevelElement.h>
#include <ITriggerableElement.h>


class EndPoint : public LevelElement, public ITriggerableElement
{
    public:
        EndPoint();
        virtual ~EndPoint();
        EndPoint(const EndPoint& other);
        void OnTrigger();

    protected:

    private:
};

#endif // ENDPOINT_H
